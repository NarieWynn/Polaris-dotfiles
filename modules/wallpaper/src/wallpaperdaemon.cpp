#include "wallpaperdaemon.h"
#include <QDebug>

WallpaperDaemon::WallpaperDaemon(QObject *parent) : QObject(parent), m_uiProcess(nullptr) {
    m_watchdogTimer = new QTimer(this);
}

void WallpaperDaemon::startUIWatchdog(QProcess *uiProcess) {
    m_uiProcess = uiProcess;

    connect(m_watchdogTimer, &QTimer::timeout, this, [this]() {
        if (m_uiProcess && m_uiProcess->state() == QProcess::Running) {
            qWarning() << "UI Core bị treo hoặc quá thời gian phản hồi! Tự động kill để giải phóng hệ thống.";
            m_uiProcess->kill();
        }
        m_watchdogTimer->stop();
    });

    m_watchdogTimer->start(20000);
}