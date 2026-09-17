#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "viewmodels/ClusterViewModel.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    // Initialize our ViewModel
    ClusterViewModel clusterViewModel;

    QQmlApplicationEngine engine;

    // Expose the C++ ViewModel to QML context
    // This allows QML to access it using the identifier "clusterViewModel"
    engine.rootContext()->setContextProperty("clusterViewModel", &clusterViewModel);

    // Qt6 qml module loading path
    const QUrl url(QStringLiteral("qrc:/qt/qml/ClusterApp/qml/main.qml"));
    
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    
    engine.load(url);

    return app.exec();
}

