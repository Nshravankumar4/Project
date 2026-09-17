# src/services/CanSimulator.cpp - Explanation Guide

**Purpose:** This implements the IPC Client logic. It proves your knowledge of Multithreading (moving sockets to a background thread) and IPC (Deserializing socket data).

### Complete Code & Line-by-Line Explanation

```cpp
#include "CanSimulator.h"
#include <QDataStream>
#include <QDebug>

// The exact same IPC socket name used by the VehicleService server.
const QString SERVER_NAME = "AutomotiveIpcSocket";

CanSimulator::CanSimulator(QObject *parent) 
    : QObject(parent), m_thread(std::make_unique<QThread>()), m_socket(nullptr), m_reconnectTimer(nullptr)
{
    // ------------------------------------------------------------------
    // MULTITHREADING: We move this object to a background thread.
    // This ensures that slow IPC/Network operations do NOT block the QML UI.
    // ------------------------------------------------------------------
    this->moveToThread(m_thread.get());

    // When the thread actually starts, it will trigger initIpcConnection()
    connect(m_thread.get(), &QThread::started, this, &CanSimulator::initIpcConnection);
}

CanSimulator::~CanSimulator() {
    stopSimulation(); // Safely stop the background thread before destroying
}

void CanSimulator::startSimulation() {
    if (!m_thread->isRunning()) {
        m_thread->start(); // This kicks off the background thread
    }
}

void CanSimulator::stopSimulation() {
    if (m_thread->isRunning()) {
        m_thread->quit(); // Tell thread to exit event loop
        m_thread->wait(); // Block main thread until background thread actually finishes
    }
}

void CanSimulator::initIpcConnection() {
    // 1. Objects created inside this method live on the background thread!
    // We pass 'this' as the parent so Qt manages their memory.
    m_socket = new QLocalSocket(this);
    m_reconnectTimer = new QTimer(this);

    // 2. Connect socket events to our slot functions
    connect(m_socket, &QLocalSocket::readyRead, this, &CanSimulator::onReadyRead);
    connect(m_socket, &QLocalSocket::disconnected, this, &CanSimulator::onDisconnected);
    
    // 3. Auto-Reconnect logic: A C++ lambda function that checks if the socket is dead, 
    // and if so, tries to reconnect to the SERVER_NAME every 1000ms.
    connect(m_reconnectTimer, &QTimer::timeout, this, [this]() {
        if (m_socket->state() == QLocalSocket::UnconnectedState) {
            m_socket->connectToServer(SERVER_NAME);
        }
    });

    m_reconnectTimer->start(1000); 
    m_socket->connectToServer(SERVER_NAME); // Initial connection attempt
}

void CanSimulator::onDisconnected() {
    qDebug() << "Lost connection to VehicleService. Attempting to reconnect...";
}

void CanSimulator::onReadyRead() {
    // 4. Data has arrived over the IPC Socket! We wrap the socket in a QDataStream.
    QDataStream in(m_socket);
    in.setVersion(QDataStream::Qt_6_0);

    // Read all available data from the IPC socket buffer
    while (!in.atEnd()) {
        int speed = 0, rpm = 0, batterySoc = 0;
        
        // 5. Deserialization: Extract the binary data into our integers
        in >> speed >> rpm >> batterySoc;

        // 6. CROSS-THREAD COMMUNICATION:
        // Because this class lives on the background thread, calling 'emit' sends a 
        // message across thread boundaries. The ViewModel (living on the main thread) 
        // will receive this data safely via Qt's Event Loop queuing.
        emit speedReceived(speed);
        emit rpmReceived(rpm);
        emit batterySocReceived(batterySoc);
    }
}
```

