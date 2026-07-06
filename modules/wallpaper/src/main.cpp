#include <QQuickView>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickItem>
#include <LayerShellQt/Window>
#include "wallpapermanager.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQuickView view;
    view.setResizeMode(QQuickView::SizeViewToRootObject);

    WallpaperManager wpManager;

    view.engine()->rootContext()->setContextProperty("wallpaperManager", &wpManager);

    LayerShellQt::Window *layerWindow = LayerShellQt::Window::get(&view);
    if (layerWindow) {
        layerWindow->setLayer(LayerShellQt::Window::LayerOverlay);
        layerWindow->setScope("polaris-wallpaper-picker");
        layerWindow->setAnchors(LayerShellQt::Window::AnchorBottom);
        layerWindow->setMargins(QMargins(0, 0, 0, 300));
        layerWindow->setKeyboardInteractivity(LayerShellQt::Window::KeyboardInteractivityExclusive);
    }

    view.setColor(Qt::transparent);
    using namespace Qt::StringLiterals;
    view.setSource(QUrl(u"qrc:/Polaris/Wallpaper/qml/main.qml"_s));
    view.show();

    if (view.rootObject()) {
        QObject::connect(view.rootObject(), &QQuickItem::widthChanged, [&view]() {
            view.setWidth(view.rootObject()->width());
        });
        view.setWidth(view.rootObject()->width());
        QObject::connect(view.engine(), &QQmlEngine::quit, [&view]() {
            view.close();
        });

        view.rootObject()->forceActiveFocus();
    }

    return app.exec();
}