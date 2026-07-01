#pragma once
#include <QAbstractListModel>
#include <QList>

struct AppInfo {
    QString name;
    QString exec;
    QString icon;
};

class AppModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit AppModel(QObject *parent = nullptr);
    static Q_INVOKABLE void launchApp(const QString &exec);
    [[nodiscard]] int rowCount(const QModelIndex &parent) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

private:
    enum AppRoles {
        NameRole = Qt::UserRole + 1,
        ExecRole,
        IconRole
    };

    QList<AppInfo> m_apps;

    void loadApps();
};