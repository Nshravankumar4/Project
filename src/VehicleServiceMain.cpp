#include <QCoreApplication>
#include "services/MockCanServer.h"

// -------------------------------------------------------------
// This executable represents the 'Middleware / Decode' or 'QNX Process'
// from your JD architecture map. It runs independently of the UI.
// -------------------------------------------------------------
int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    MockCanServer server;
    if (!server.startServer()) {
        return -1;
    }

    // The Qt Event Loop runs here, handling IPC Socket connections
    return app.exec();
}

