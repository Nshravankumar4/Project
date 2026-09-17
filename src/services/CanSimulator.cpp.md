# src/services/CanSimulator.cpp - Explanation Guide

**Purpose:** This implements the IPC Client logic. It proves your knowledge of Multithreading (moving sockets to a background thread) and IPC (Deserializing massive socket data).

### Complete Code & Line-by-Line Explanation

```cpp
#include "CanSimulator.h"
#include <QDataStream>
#include <QDebug>

const QString SERVER_NAME = "AutomotiveIpcSocket";

CanSimulator::CanSimulator(QObject *parent) 
    : QObject(parent), m_thread(std::make_unique<QThread>()), m_socket(nullptr), m_reconnectTimer(nullptr)
{
    // MULTITHREADING: Move to background thread so IPC parsing doesn't freeze the GUI
    this->moveToThread(m_thread.get());
    connect(m_thread.get(), &QThread::started, this, &CanSimulator::initIpcConnection);
}

CanSimulator::~CanSimulator() {
    stopSimulation();
}

void CanSimulator::startSimulation() {
    if (!m_thread->isRunning()) {
        m_thread->start();
    }
}

void CanSimulator::stopSimulation() {
    if (m_thread->isRunning()) {
        m_thread->quit();
        m_thread->wait(); 
    }
}

void CanSimulator::initIpcConnection() {
    m_socket = new QLocalSocket(this);
    m_reconnectTimer = new QTimer(this);

    connect(m_socket, &QLocalSocket::readyRead, this, &CanSimulator::onReadyRead);
    connect(m_socket, &QLocalSocket::disconnected, this, &CanSimulator::onDisconnected);
    
    // Auto-Reconnect lambda
    connect(m_reconnectTimer, &QTimer::timeout, this, [this]() {
        if (m_socket->state() == QLocalSocket::UnconnectedState) {
            m_socket->connectToServer(SERVER_NAME);
        }
    });

    m_reconnectTimer->start(1000); 
    m_socket->connectToServer(SERVER_NAME);
}

void CanSimulator::onDisconnected() {
    qDebug() << "Lost connection to VehicleService. Attempting to reconnect...";
}

void CanSimulator::onReadyRead() {
    QDataStream in(m_socket);
    in.setVersion(QDataStream::Qt_6_0);

    // Read all available data from the IPC socket buffer
    while (!in.atEnd()) {
        int speed = 0, rpm = 0, batterySoc = 0, turnSignal = 0, odometer = 0, range = 0, adasDistance = 0, menuIndex = 0;
        QString gear, alertMessage;
        
        // Deserialization: Extract the binary data perfectly in order
        in >> speed >> rpm >> batterySoc >> gear >> turnSignal >> odometer >> range >> adasDistance >> menuIndex >> alertMessage;

        // CROSS-THREAD COMMUNICATION: Send data to the main thread securely
        emit speedReceived(speed);
        emit rpmReceived(rpm);
        emit batterySocReceived(batterySoc);
        emit gearReceived(gear);
        emit turnSignalReceived(turnSignal);
        emit odometerReceived(odometer);
        emit rangeReceived(range);
        emit adasDistanceReceived(adasDistance);
        emit menuIndexReceived(menuIndex);
        emit alertMessageReceived(alertMessage);
    }
}
```
