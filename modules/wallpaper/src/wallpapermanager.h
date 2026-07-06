#ifndef WALLPAPERMANAGER_H
#define WALLPAPERMANAGER_H

#include <QObject>
#include <QString>
#include <QStringList>

class WallpaperManager : public QObject {
    Q_OBJECT

public:
    explicit WallpaperManager(QObject *parent = nullptr);

    Q_INVOKABLE QStringList loadWallpapers() const;
    Q_INVOKABLE void setWallpaper(const QString &filePath);

    Q_INVOKABLE int getCurrentWallpaperIndex(const QStringList &wallpapers) const;
};

#endif // WALLPAPERMANAGER_H