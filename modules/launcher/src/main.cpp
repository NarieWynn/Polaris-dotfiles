#include <QGuiApplication>
#include <QQmlApplicationEngine>
//#include <QDirIterator>
#include "appmodel.h"
#include <QQmlContext>
#include <QSettings>
#include <QSortFilterProxyModel>

using namespace Qt::StringLiterals;

int main(int argc, char *argv[]) {

#ifdef HAS_VULKAN
    qputenv("QSG_RHI_BACKEND", "vulkan");
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    const QUrl url(u"qrc:/qt/qml/polaris/qml/main.qml"_s);
    AppModel model;

    QSortFilterProxyModel proxy;
    proxy.setSourceModel(&model);
    proxy.setFilterRole(Qt::UserRole + 1); // NameRole
    proxy.setFilterCaseSensitivity(Qt::CaseInsensitive);

    engine.rootContext()->setContextProperty("appModel", &proxy);
    engine.rootContext()->setContextProperty("searchProxy", &proxy);
    engine.rootContext()->setContextProperty("appModelSource", &model);

    engine.load(url);

    return QGuiApplication::exec();
}
