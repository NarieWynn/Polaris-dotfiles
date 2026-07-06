#ifndef WALLPAPERDAEMON_H
#define WALLPAPERDAEMON_H
#include <QTimer>
#include <QProcess>

class WallpaperDaemon : public QObject {
    Q_OBJECT
public:
    explicit WallpaperDaemon(QObject *parent = nullptr);
    void startUIWatchdog(QProcess *uiProcess);

private:
    QTimer *m_watchdogTimer;
    QProcess *m_uiProcess;
};

#endif