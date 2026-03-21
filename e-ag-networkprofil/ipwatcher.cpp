#include "ipwatcher.h"

#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <QDebug>

IPWatcher::IPWatcher(QObject *parent) : QObject(parent)
{
    // 🔧 Netlink socket oluştur
    netlinkSocket = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (netlinkSocket < 0) {
        perror("socket");
        return;
    }

    // Non-blocking yap
    fcntl(netlinkSocket, F_SETFL, O_NONBLOCK);

    sockaddr_nl addr{};
    addr.nl_family = AF_NETLINK;
    addr.nl_groups = RTMGRP_LINK | RTMGRP_IPV4_IFADDR | RTMGRP_IPV6_IFADDR;

    if (bind(netlinkSocket, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind");
        close(netlinkSocket);
        netlinkSocket = -1;
        return;
    }

    // 🔌 Qt notifier
    notifier = new QSocketNotifier(netlinkSocket, QSocketNotifier::Read, this);
    connect(notifier, &QSocketNotifier::activated, this, &IPWatcher::handleNetlinkEvent);

    // 📌 İlk IP’leri al
    lastIPs = getCurrentIPs();
    qDebug() << "Initial IPs:" << lastIPs;
}

IPWatcher::~IPWatcher()
{
    if (netlinkSocket >= 0)
        close(netlinkSocket);
}

void IPWatcher::handleNetlinkEvent()
{
    if (!notifier) return;

    notifier->setEnabled(false);

    char buffer[4096];

    while (true) {
        int len = recv(netlinkSocket, buffer, sizeof(buffer), MSG_DONTWAIT);
        if (len <= 0)
            break;

        for (nlmsghdr* nh = (nlmsghdr*)buffer;
             NLMSG_OK(nh, len);
             nh = NLMSG_NEXT(nh, len)) {

            // IP değişimi veya interface event
            if (nh->nlmsg_type == RTM_NEWADDR ||
                nh->nlmsg_type == RTM_DELADDR ||
                nh->nlmsg_type == RTM_NEWLINK ||
                nh->nlmsg_type == RTM_DELLINK) {

                QStringList currentIPs = getCurrentIPs();

                if (currentIPs != lastIPs) {
                    lastIPs = currentIPs;
                    qDebug() << "IP değişti:" << currentIPs;
                    emit ipChanged(currentIPs);
                }
            }
        }
    }

    notifier->setEnabled(true);
}

// 🔧 Tüm aktif IPv4 IP’lerini döndür
QStringList IPWatcher::getCurrentIPs()
{
    QStringList list;

    for (const QNetworkInterface &iface : QNetworkInterface::allInterfaces()) {

        if (!(iface.flags() & QNetworkInterface::IsUp) ||
            (iface.flags() & QNetworkInterface::IsLoopBack))
            continue;

        // VirtualBox / host-only / virbr interface’leri atla
        ///if (iface.name().contains("vbox") || iface.name().contains("virbr"))
         //   continue;

        for (const QNetworkAddressEntry &entry : iface.addressEntries()) {
            if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
                list << entry.ip().toString();
        }
    }

    return list;
}
