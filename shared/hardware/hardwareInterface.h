#pragma once
#include <QObject>

class HardwareInterface : public QObject {
    Q_OBJECT
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(int brightness READ brightness WRITE setBrightness NOTIFY brightnessChanged)

public:
    explicit HardwareInterface(QObject *parent = nullptr);

    [[nodiscard]]int volume() const { return m_volume; }
    void setVolume(int val);
    [[nodiscard]]int brightness() const { return m_brightness; }
    void setBrightness(int val);
    Q_INVOKABLE void adjustVolume(int delta);
    Q_INVOKABLE void adjustBrightness(int delta);

    signals:
        void volumeChanged(int val);
    void brightnessChanged(int val);

private:
    int m_volume{50};
    int m_brightness{50};
    void syncFromSystem();
    static void executeCommand(const char* program, char* const argv[]);
    void updateSystemVolume();
    void updateSystemBrightness();
};