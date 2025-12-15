#ifndef USERPRIVILEGEHELPER_H
#define USERPRIVILEGEHELPER_H

#include <QObject>
#include <QString>
#include <QProcess>
#include <QTimer>
#include <QProcessEnvironment>
// userprivilegehelper.h içinde
// userprivilegehelper.h içinde
struct SessionInfo {
    QString username;
    int uid;
    int gid;
    QString home;
    QString display;
    QString type;       // x11, wayland, vs
    QString service;    // GDM, SDDM, vs
    bool valid = false;
};

struct UserInfo {
    QString username;
    int uid;
    int gid;
    QString home;
    QString sessionId;
    bool valid = false;
};


class UserPrivilegeHelper : public QObject
{
    Q_OBJECT
public:
    explicit UserPrivilegeHelper(QObject *parent = nullptr);

    // KULLANICI TESPİT  
    SessionInfo getActiveSessionInfo();
    QString detectActiveSession();
    QString detectActiveUser();
    UserInfo getUserInfo(const QString &user);


    // ÇEVRE DEĞİŞKENLERİ
    QProcessEnvironment buildUserEnvironment(const UserInfo &u);

    // ÇALIŞTIRMA FONKSİYONLARI
    bool runAsUser(const UserInfo &u, const QString &cmd,
                   const QProcessEnvironment &env = QProcessEnvironment());
    bool runAsUserDetached(const UserInfo &u, const QString &cmd,
                           const QProcessEnvironment &env = QProcessEnvironment());


    bool runAsUserG(const UserInfo &info, const QString &cmd,
                                         const QProcessEnvironment &env);
    // YARDIMCI FONKSİYONLAR
    bool sendNotification(const UserInfo &u, const QString &title, const QString &msg);
    bool runGuiApp(const UserInfo &u, const QString &app);
    bool runCommand(const UserInfo &u, const QString &cmd);
    QProcessEnvironment buildUserEnvironmentForPkexec(const UserInfo &u);
    bool runGuiAsActiveUserPkexec(const QString &cmd);

    // OTOMATİK KULLANICI TAKİBİ
    void startUserMonitor(int intervalMs = 3000);
    // Aktif kullanıcı GUI programı başlat
    bool runGuiAppAsActiveUser(const QString &cmd);
signals:
    void activeUserChanged(const UserInfo &user);

private slots:
    void checkUser();

private:
    UserInfo currentUser;
     SessionInfo currentSession;  // <-- Burayı ekle
};

#endif // USERPRIVILEGEHELPER_H
