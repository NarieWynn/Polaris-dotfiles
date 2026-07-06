#include "wallpapermanager.h"
#include <QDir>
#include <QProcess>
#include <QUrl>

WallpaperManager::WallpaperManager(QObject *parent) : QObject(parent) {}

QStringList WallpaperManager::loadWallpapers() const {
    QStringList urls;
    QString path = QDir::homePath() + "/Pictures/WallPapers";
    QDir dir(path);
    QStringList filters = {"*.png", "*.jpg", "*.jpeg"};
    QStringList files = dir.entryList(filters, QDir::Files);

    for (const QString &file : files) {
        urls.append(QUrl::fromLocalFile(path + "/" + file).toString());
    }
    return urls;
}

void WallpaperManager::setWallpaper(const QString &filePath) {
    if (filePath.isEmpty()) return;

    QString cleanPath = filePath;
    if (cleanPath.startsWith("file://")) {
        cleanPath = cleanPath.mid(7);
    }

    QProcess::startDetached("hyprctl", QStringList() << "hyprpaper" << "preload" << cleanPath);
    QProcess::startDetached("hyprctl", QStringList() << "hyprpaper" << "wallpaper" << "eDP-1," + cleanPath);
}


int WallpaperManager::getCurrentWallpaperIndex(const QStringList &wallpapers) const {
    QProcess proc;
    proc.start("hyprctl", QStringList() << "hyprpaper" << "current");
    proc.waitForFinished();
    QString output = QString::fromUtf8(proc.readAllStandardOutput()).trimmed();

    if (output.isEmpty() || !output.contains("=")) return 0;

    QString currentPath = output.split("=").last().trimmed();
    QString currentUrl = QUrl::fromLocalFile(currentPath).toString();

    for (int i = 0; i < wallpapers.size(); ++i) {
        if (wallpapers[i] == currentUrl) {
            return i;
        }
    }
    return 0;
}