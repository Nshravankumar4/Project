# src/VehicleServiceMain.cpp - Explanation Guide

**Purpose:** This is the entry point for the **second process** (the background vehicle daemon). It proves your knowledge of multi-process architecture and IPC servers.

### Complete Code & Line-by-Line Explanation

```cpp
#include <QCoreApplication>
#include "services/MockCanServer.h"

// -------------------------------------------------------------
// This executable represents the 'Middleware / Decode' or 'QNX Process'
// from your JD architecture map. It runs independently of the UI.
// -------------------------------------------------------------
int main(int argc, char *argv[]) {
    
    // 1. We use QCoreApplication instead of QGuiApplication because this is a 
    // "headless" background daemon. It has no UI, so it uses less memory.
    QCoreApplication app(argc, argv);

    // 2. Instantiate our custom MockCanServer class.
    MockCanServer server;
    
    // 3. Attempt to start the server (which opens the Local Socket).
    if (!server.startServer()) {
        // If it fails (e.g. socket is blocked), exit the program with an error code.
        return -1;
    }

    // 4. Start the Qt Event Loop. 
    // Even though there is no UI, we need the event loop to listen for incoming 
    // network/IPC connections and to run QTimers.
    return app.exec();
}
```

