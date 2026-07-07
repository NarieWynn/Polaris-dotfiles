#include <QQuickView>
#include <QQmlContext>
#include <QQmlEngine>
#include <QWindow>
#include <QMargins>
#include <LayerShellQt/Window>
#include <hardware/hardwareInterface.h>
#include <iostream>

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QString mode = "none";
    int delta = 0;

    if (argc > 1) {
        QString arg1 = argv[1];

        if (arg1 == "--volume-up")   { mode = "volume";     delta = 5; }
        else if (arg1 == "--volume-down") { mode = "volume";     delta = -5; }
        else if (arg1 == "--brightness-up") { mode = "brightness"; delta = 5; }
        else if (arg1 == "--brightness-down") { mode = "brightness"; delta = -5; }

        else if (argc > 2) {
            QString action = argv[2];
            if (arg1 == "--volume") {
                mode = "volume";
                delta = (action == "up") ? 5 : -5;
            } else if (arg1 == "--brightness") {
                mode = "brightness";
                delta = (action == "up") ? 5 : -5;
            }
        }
    }

    QQuickView view;
    view.setResizeMode(QQuickView::SizeViewToRootObject);


    HardwareInterface *hw = new HardwareInterface(&app);

    if (mode == "volume") {
        hw->adjustVolume(delta);
    } else if (mode == "brightness") {
        hw->adjustBrightness(delta);
    }

    std::cout << "🟢 [Polaris Backend] Final Target -> Volume: " << hw->volume()
              << "%, Brightness: " << hw->brightness() << "%" << std::endl;

    view.engine()->rootContext()->setContextProperty("hardwareManager", hw);
    view.engine()->rootContext()->setContextProperty("osdMode", mode);

    LayerShellQt::Window *layerWindow = LayerShellQt::Window::get(&view);
    if (layerWindow) {
        layerWindow->setLayer(LayerShellQt::Window::LayerOverlay);
        layerWindow->setScope("polaris-osd");
        layerWindow->setAnchors(LayerShellQt::Window::AnchorBottom);
        layerWindow->setMargins(QMargins(0, 0, 0, 100));
    }

    view.setColor(Qt::transparent);

    using namespace Qt::StringLiterals;
    view.setSource(QUrl(u"qrc:/Polaris/OSD/qml/main.qml"_s));
    view.show();

    QObject::connect(view.engine(), &QQmlEngine::quit, &app, &QCoreApplication::quit);

    return QGuiApplication::exec();
}