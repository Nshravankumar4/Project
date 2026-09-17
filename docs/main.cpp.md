# src/main.cpp - Explanation Guide

**Purpose:** This is the entry point for the GUI Application. It initializes the Qt Application, creates the QML Engine, and injects our C++ ViewModel into the QML environment so the UI can read the data.

### Complete Code & Line-by-Line Explanation

```cpp
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "viewmodels/ClusterViewModel.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    // Enable High DPI scaling for older Qt5 versions so the UI looks good on 4K screens
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    // 1. Initialize the main GUI Application object. This manages the GUI event loop.
    QGuiApplication app(argc, argv);

    // 2. Initialize our C++ ViewModel. This object will handle all data from the IPC socket.
    ClusterViewModel clusterViewModel;

    // 3. Initialize the QML Engine. This is the interpreter that reads and runs your .qml files.
    QQmlApplicationEngine engine;

    // 4. C++ ↔ QML BRIDGE (Crucial for JD!):
    // We take our C++ 'clusterViewModel' object and register it inside the QML Engine.
    // By naming it "clusterViewModel", any QML file can now type `clusterViewModel.speed` 
    // to instantly read the C++ data!
    engine.rootContext()->setContextProperty("clusterViewModel", &clusterViewModel);

    // 5. Define the path to our main.qml file. 
    // We use 'qrc:/qt/qml/...' because CMake embedded the QML files into the binary as a resource.
    const QUrl url(QStringLiteral("qrc:/qt/qml/ClusterApp/qml/main.qml"));
    
    // 6. Error handling: If the QML engine creates the object but it fails (e.g. syntax error in QML),
    // we safely exit the C++ application.
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    
    // 7. Actually load the QML file to display the UI on screen.
    engine.load(url);

    // 8. Start the Qt Event Loop. This pauses the main() function here and keeps the app running
    // until the user closes the window.
    return app.exec();
}
```

