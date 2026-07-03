#ifndef BATTERY_H
#define BATTERY_H
#include <QObject>
#include <QTimer>

class BatteryManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(int batteryLevel READ batteryLevel NOTIFY batteryChanged)
    Q_PROPERTY(bool isCharging READ isCharging NOTIFY batteryChanged)

public:
    explicit BatteryManager(QObject *parent = nullptr);

    int batteryLevel() const;
    bool isCharging() const;

    signals:
        void batteryChanged();

private slots:
    // Hàm này sẽ được QTimer gọi liên tục để cập nhật số liệu thời gian thực
    void updateBatteryStatus();

private:
    int m_batteryLevel = 0;
    bool m_isCharging = false;
    QTimer *m_timer;
};

#endif // BATTERY_H