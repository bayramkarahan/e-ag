#ifndef FUNTION_H
#define FUNTION_H
#include <stdio.h>
#include <stdlib.h>
#include <QProcessEnvironment>
#include <QString>
#include <iostream>
#include <QString>
#if defined(Q_OS_WIN)
#include <windows.h>
#include <tlhelp32.h>
#endif

/*
UserPrivilegeHelper helper;

connect(&helper, &UserPrivilegeHelper::activeUserChanged, [&](UserInfo u){
    qDebug() << "Aktif kullanıcı değişti:" << u.username;
});

// otomatik takip
helper.startUserMonitor();

// aktif kullanıcıyı al
QString user = helper.detectActiveUser();
UserInfo info = helper.getUserInfo(user);

// GUI program çalıştır
helper.runGuiApp(info, "xterm");

// kullanıcıya bildirim
helper.sendNotification(info, "Root Uygulama", "Merhaba kullanıcı!");

// kullanıcı terminal komutu
helper.runCommand(info, "touch ~/dosya.txt");

*/
bool MainWindow::killProcessByName(const QString &processName) {
    #if defined(Q_OS_WIN)
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap == INVALID_HANDLE_VALUE) return false;

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hSnap, &pe)) {
        CloseHandle(hSnap);
        return false;
    }

    bool success = false;
    do {
        if (QString::fromWCharArray(pe.szExeFile).compare(processName, Qt::CaseInsensitive) == 0) {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
            if (hProcess) {
                TerminateProcess(hProcess, 0);
                CloseHandle(hProcess);
                success = true;
            }
        }
    } while (Process32Next(hSnap, &pe));

    CloseHandle(hSnap);
    return success;
    #endif
}

void MainWindow::selectSlot()
{
    for(int i=0;i<onlinePcList.count();i++)
    {
        // onlinePcList[i]->select=!(onlinePcList[i]->select);
        /// onlinePcList[i]->slotMouseClick();
        onlinePcList[i]->slotMouseDoubleClick();
    }
    mesajSlot("Host Seçimi Yapıldı.");
}



#endif // FUNTION_H
