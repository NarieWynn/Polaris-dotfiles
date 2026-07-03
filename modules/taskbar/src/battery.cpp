#include "battery.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>

BatteryManager::BatteryManager(QObject *parent) : QObject(parent) {
    m_timer = new QTimer(this);

    // Kết nối culi thời gian: Cứ mỗi khi timer báo chuông thì gọi hàm cập nhật
    connect(m_timer, &QTimer::timeout, this, &BatteryManager::updateBatteryStatus);

    // Bắn phát súng đầu tiên để lấy data ngay khi vừa boot Taskbar lên
    updateBatteryStatus();

    // Cứ mỗi 3000ms (3 giây) quét file ảo một lần. Pin tụt không nhanh nên 3s là cực kỳ tối ưu RAM!
    m_timer->start(3000);
}

void BatteryManager::updateBatteryStatus() {
    QDir dir("/sys/class/power_supply");

    // Quét động tất cả thư mục bắt đầu bằng BAT
    QStringList filters;
    filters << "BAT*";
    dir.setNameFilters(filters);

    QStringList batteries = dir.entryList(QDir::Dirs);

    if (batteries.isEmpty()) {
        qWarning() << "There is no battery in sysfs!";
        return;
    }

    // Tự động bốc thằng pin đầu tiên (Máy mày sẽ tự ăn vào "BAT1" cực uy tín)
    QString batName = batteries.first();
    QString basePath = "/sys/class/power_supply/" + batName + "/";

    int newLevel = m_batteryLevel;
    bool newCharging = m_isCharging;

    // 1. ĐỌC PHẦN TRĂM PIN TỪ FILE ẢO CỦA KERNEL
    QFile fileCapacity(basePath + "capacity");
    if (fileCapacity.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&fileCapacity);
        newLevel = in.readLine().trimmed().toInt();
        fileCapacity.close();
    }

    // 2. ĐỌC TRẠNG THÁI SẠC TỪ FILE ẢO CỦA KERNEL
    QFile fileStatus(basePath + "status");
    if (fileStatus.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&fileStatus);
        QString status = in.readLine().trimmed();
        newCharging = (status == "Charging");
        fileStatus.close();
    }

    // 3. SO SÁNH BIẾN ĐỔI: Chỉ khi nào pin tụt/tăng hoặc trạng thái sạc thay đổi thì mới bắn signal lên UI
    if (newLevel != m_batteryLevel || newCharging != m_isCharging) {
        m_batteryLevel = newLevel;
        m_isCharging = newCharging;
        emit batteryChanged(); // Bùa chú kích hoạt QML render lại số mới
        qDebug() << "Battery updated dynamically:" << m_batteryLevel << "%" << (m_isCharging ? "(Charging)" : "");
    }
}

int BatteryManager::batteryLevel() const {
    return m_batteryLevel;
}

bool BatteryManager::isCharging() const {
    return m_isCharging;
}