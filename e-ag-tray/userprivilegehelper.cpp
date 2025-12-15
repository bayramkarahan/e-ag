#include "userprivilegehelper.h"
#include <QDebug>
#include <QRegularExpression>
#include <pwd.h>
#include <unistd.h>         // fork, setuid, setgid, execvp
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>         // setenv
#include <string.h>         // strdup
#include <QDir>
#include <QFile>
#include <QProcessEnvironment>

/* ================================================================
 * Constructor
 * ================================================================ */
UserPrivilegeHelper::UserPrivilegeHelper(QObject *parent)
    : QObject(parent)
{
}


/* ================================================================
 * UID/GID bilgilerini elde et
 * ================================================================ */
UserInfo UserPrivilegeHelper::getUserInfo(const QString &user)
{
    UserInfo u;

    struct passwd *pw = getpwnam(user.toUtf8().data());
    if (!pw) return u;

    u.username = user;
    u.uid = pw->pw_uid;
    u.gid = pw->pw_gid;
    u.home = pw->pw_dir;
    u.valid = true;

    u.sessionId = detectActiveSession();

    return u;
}

/* ================================================================
 * Kullanıcı için X11/Wayland/DBus ortamı hazırlama
 * ================================================================ */
QProcessEnvironment UserPrivilegeHelper::buildUserEnvironment(const UserInfo &u)
{
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    env.insert("USER", u.username);
    env.insert("LOGNAME", u.username);
    env.insert("HOME", u.home);

    env.insert("DISPLAY", ":0");
    env.insert("XAUTHORITY", u.home + "/.Xauthority");
    env.insert("XDG_RUNTIME_DIR", "/run/user/" + QString::number(u.uid));

    // DBus session adresini otomatik bul
    QString dbusAddress;
    QByteArray dbusEnv = qgetenv("DBUS_SESSION_BUS_ADDRESS");
    if (!dbusEnv.isEmpty()) {
        dbusAddress = QString::fromUtf8(dbusEnv);
    } else {
        // fallback: /tmp/dbus-* içinde socket ara
        QDir tmpDir("/tmp");
        QStringList files = tmpDir.entryList(QStringList() << "dbus-*", QDir::Files);
        if (!files.isEmpty())
            dbusAddress = "unix:path=/tmp/" + files.first();
    }
    if (!dbusAddress.isEmpty())
        env.insert("DBUS_SESSION_BUS_ADDRESS", dbusAddress);

    return env;
}

/* ================================================================
 * Kullanıcı olarak komut çalıştır
 * ================================================================ */
bool UserPrivilegeHelper::runAsUser(const UserInfo &u,
                                    const QString &cmd,
                                    const QProcessEnvironment &env)
{
    QProcess p;
    if (!env.isEmpty())
        p.setProcessEnvironment(env);

    QStringList args;
    args << "-u" << u.username << "bash" << "-c" << cmd;

    p.start("sudo", args);
    bool ok = p.waitForFinished();

    qDebug() << p.readAllStandardOutput();
    qDebug() << p.readAllStandardError();

    return ok;
}

/* ================================================================
 * Detached çalıştır
 * ================================================================ */
bool UserPrivilegeHelper::runAsUserDetached(const UserInfo &u,
                                            const QString &cmd,
                                            const QProcessEnvironment &env)
{
    QProcess *p = new QProcess();
    if (!env.isEmpty()) p->setProcessEnvironment(env);

    QStringList args;
    args << "-u" << u.username << "bash" << "-c" << cmd;

    return p->startDetached("sudo", args);
}

/* ================================================================
 * Kullanıcıya notify-send ile bildirim gönder
 * ================================================================ */
bool UserPrivilegeHelper::sendNotification(const UserInfo &u,
                                           const QString &title,
                                           const QString &msg)
{
    QString cmd = QString("notify-send '%1' '%2'").arg(title, msg);
    return runCommand(u, cmd);
}

/* ================================================================
 * Kullanıcıya GUI uygulaması çalıştır
 * ================================================================ */
bool UserPrivilegeHelper::runGuiApp(const UserInfo &u, const QString &app)
{
    return runCommand(u, app);
}

/* ================================================================
 * Kullanıcı adına basic komut
 * ================================================================ */
bool UserPrivilegeHelper::runCommand(const UserInfo &u, const QString &cmd)
{
    auto env = buildUserEnvironment(u);
    return runAsUser(u, cmd, env);
}

/* ================================================================
 * Root → User GUI çalıştır
 * ================================================================ */
bool UserPrivilegeHelper::runAsUserG(const UserInfo &info,
                                     const QString &cmd,
                                     const QProcessEnvironment &env)
{
    pid_t pid = fork();
    if (pid < 0) {
        return false;
    }

    if (pid == 0)
    {
        // ---- CHILD ----
        setgid(info.gid);
        setuid(info.uid);

        // Env değişkenleri ekle
        for (const QString &key : env.keys()) {
            QByteArray k = key.toUtf8();
            QByteArray v = env.value(key).toUtf8();
            setenv(k.constData(), v.constData(), 1);
        }

        // Komutu parçala
        QStringList parts = cmd.split(' ', Qt::SkipEmptyParts);
        std::vector<char*> argv;
        argv.reserve(parts.size() + 1);

        for (const QString &p : parts) {
            QByteArray ba = p.toUtf8();
            argv.push_back(strdup(ba.constData()));
        }
        argv.push_back(nullptr);

        execvp(argv[0], argv.data());
        _exit(1);
    }

    return true;
}

/* ================================================================
 * Kullanıcı değişti mi? Takip et
 * ================================================================ */
void UserPrivilegeHelper::startUserMonitor(int intervalMs)
{
    QTimer *t = new QTimer(this);
    connect(t, &QTimer::timeout, this, &UserPrivilegeHelper::checkUser);
    t->start(intervalMs);

    checkUser();
}

void UserPrivilegeHelper::checkUser()
{
    QString user = detectActiveUser();
    if (user.isEmpty()) return;

    if (currentUser.username != user) {
        currentUser = getUserInfo(user);
        emit activeUserChanged(currentUser);
    }
}

/* ================================================================
 * Root Qt uygulamasından aktif kullanıcı GUI açma
 * ================================================================ */
bool UserPrivilegeHelper::runGuiAppAsActiveUser(const QString &cmd)
{
    QString user = detectActiveUser();
    if (user.isEmpty()) return false;

    UserInfo info = getUserInfo(user);
    QProcessEnvironment env = buildUserEnvironment(info);

    return runAsUserG(info, cmd, env);
}


QProcessEnvironment UserPrivilegeHelper::buildUserEnvironmentForPkexec(const UserInfo &u)
{
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    // Temel kullanıcı bilgileri
    env.insert("USER", u.username);
    env.insert("LOGNAME", u.username);
    env.insert("HOME", u.home);

    // X11 ve Wayland ortam değişkenleri
    env.insert("DISPLAY", ":0");
    env.insert("XAUTHORITY", u.home + "/.Xauthority");
    env.insert("XDG_RUNTIME_DIR", "/run/user/" + QString::number(u.uid));

    // DBus session fallback
    QString dbusAddress = QString("unix:path=/run/user/%1/bus").arg(u.uid);
    env.insert("DBUS_SESSION_BUS_ADDRESS", dbusAddress);

    return env;
}

bool UserPrivilegeHelper::runGuiAsActiveUserPkexec(const QString &cmd)
{
    // 1️⃣ Aktif kullanıcıyı tespit et
    QString user = detectActiveUser();
    if (user.isEmpty()) {
        qWarning() << "Aktif kullanıcı bulunamadı!";
        return false;
    }

    UserInfo info = getUserInfo(user);

    // 2️⃣ Ortam değişkenlerini hazırla
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("USER", info.username);
    env.insert("LOGNAME", info.username);
    env.insert("HOME", info.home);
    env.insert("DISPLAY", ":0");
    env.insert("XAUTHORITY", info.home + "/.Xauthority");
    env.insert("XDG_RUNTIME_DIR", "/run/user/" + QString::number(info.uid));

    // DBus session adresini otomatik bul
    QString dbusAddress;
    QByteArray dbusEnv = qgetenv("DBUS_SESSION_BUS_ADDRESS");
    if (!dbusEnv.isEmpty()) {
        dbusAddress = QString::fromUtf8(dbusEnv);
    } else {
        // fallback: /run/user/<uid>/bus
        QString busFile = QString("/run/user/%1/bus").arg(info.uid);
        if (QFile::exists(busFile)) {
            dbusAddress = "unix:path=" + busFile;
        }
    }
    if (!dbusAddress.isEmpty()) {
        env.insert("DBUS_SESSION_BUS_ADDRESS", dbusAddress);
    }

    // 3️⃣ Fork + setuid/setgid ile GUI uygulamasını başlat
    pid_t pid = fork();
    if (pid < 0) {
        qWarning() << "Fork başarısız!";
        return false;
    }

    if (pid == 0)
    {
        // ---- CHILD ----
        setgid(info.gid);
        setuid(info.uid);

        // Ortam değişkenlerini set et
        for (const QString &key : env.keys()) {
            QByteArray k = key.toUtf8();
            QByteArray v = env.value(key).toUtf8();
            setenv(k.constData(), v.constData(), 1);
        }

        // Komutu parçala ve exec
        QStringList parts = cmd.split(' ', Qt::SkipEmptyParts);
        std::vector<char*> argv;
        argv.reserve(parts.size() + 1);
        for (const QString &p : parts)
            argv.push_back(strdup(p.toUtf8().constData()));
        argv.push_back(nullptr);

        execvp(argv[0], argv.data());
        _exit(1);
    }

    // ---- PARENT ----
    return true;
}

// userprivilegehelper.cpp içinde
SessionInfo UserPrivilegeHelper::getActiveSessionInfo()
{
    SessionInfo info;

    // 1️⃣ Aktif session ID tespit et
    QString sessionId = detectActiveSession();
    if (sessionId.isEmpty()) return info;

    // 2️⃣ loginctl ile session detaylarını al
    QProcess p;
    p.start("loginctl", {"show-session", sessionId, "-p", "Name", "-p", "Display", "-p", "Type", "-p", "Service"});
    p.waitForFinished();
    QStringList lines = QString(p.readAllStandardOutput()).split("\n", Qt::SkipEmptyParts);

    QString username, display, type, service;
    for (const QString &line : lines) {
        if (line.startsWith("Name=")) username = line.mid(5).trimmed();
        else if (line.startsWith("Display=")) display = line.mid(8).trimmed();
        else if (line.startsWith("Type=")) type = line.mid(5).trimmed();
        else if (line.startsWith("Service=")) service = line.mid(8).trimmed();
    }

    if (username.isEmpty()) return info;

    // 3️⃣ UID/GID ve home bilgilerini al
    struct passwd *pw = getpwnam(username.toUtf8().constData());
    if (!pw) return info;

    info.username = username;
    info.uid = pw->pw_uid;
    info.gid = pw->pw_gid;
    info.home = pw->pw_dir;
    info.display = display.isEmpty() ? ":0" : display;
    info.type = type;
    info.service = service;
    info.valid = true;

    return info;
}

// Aktif session ID bulma (loginctl)
QString UserPrivilegeHelper::detectActiveSession()
{
    QProcess p;
    p.start("loginctl", {"list-sessions", "--no-legend"});
    p.waitForFinished();
    QStringList lines = QString(p.readAllStandardOutput()).split("\n", Qt::SkipEmptyParts);

    for (const QString &line : lines) {
        QStringList parts = line.split(QRegularExpression("\\s+"));
        if (parts.size() < 2) continue;

        QString sessionId = parts[0];

        // Grafik oturum mu?
        QProcess p2;
        p2.start("loginctl", {"show-session", sessionId, "-p", "Type"});
        p2.waitForFinished();
        QString type = p2.readAllStandardOutput().trimmed();

        if (type.contains("x11") || type.contains("wayland"))
            return sessionId;
    }

    return "";
}

// Aktif kullanıcı
QString UserPrivilegeHelper::detectActiveUser()
{
    QString session = detectActiveSession();
    if (session.isEmpty()) return "";

    QProcess p;
    p.start("loginctl", {"show-session", session, "-p", "Name"});
    p.waitForFinished();
    QString out = p.readAllStandardOutput();
    out.replace("Name=", "");
    return out.trimmed();
}
