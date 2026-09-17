# src/services/MockCanServer.cpp - Explanation Guide

**Purpose:** Implements the IPC Server, generating random data and serializing it over a Local Socket to simulate QNX process communication.

### Complete Code & Line-by-Line Explanation

```cpp
#include "MockCanServer.h"
#include <QDebug>
#include <QDataStream>
#include <random>

// The unique identifier for the IPC Socket.
const QString SERVER_NAME = "AutomotiveIpcSocket";

MockCanServer::MockCanServer(QObject *parent) 
    : QObject(parent), m_server(new QLocalServer(this)), m_timer(new QTimer(this)) 
{
    // CONNECT: When a client tries to connect, trigger onNewConnection
    connect(m_server, &QLocalServer::newConnection, this, &MockCanServer::onNewConnection);
    // CONNECT: Every time the timer ticks, trigger broadcastVehicleData
    connect(m_timer, &QTimer::timeout, this, &MockCanServer::broadcastVehicleData);
}

MockCanServer::~MockCanServer() {
    m_server->close();
}

bool MockCanServer::startServer() {
    // Remove any crashed/lingering sockets with the same name before starting
    QLocalServer::removeServer(SERVER_NAME);

    // listen() creates the actual IPC pipe in the OS
    if (m_server->listen(SERVER_NAME)) {
        qDebug() << "VehicleService (IPC Server) is running on socket:" << SERVER_NAME;
        // Start the timer to tick every 100 milliseconds
        m_timer->start(100); 
        return true;
    } else {
        qDebug() << "Failed to start IPC Server:" << m_server->errorString();
        return false;
    }
}

void MockCanServer::onNewConnection() {
    // Accept the pending client connection
    QLocalSocket* clientConnection = m_server->nextPendingConnection();
    if (clientConnection) {
        qDebug() << "AutomotiveCluster connected to IPC Server!";
        connect(clientConnection, &QLocalSocket::disconnected, this, &MockCanServer::onClientDisconnected);
        m_clients.append(clientConnection); // Keep track of the client
    }
}

void MockCanServer::onClientDisconnected() {
    // sender() gives us the object that emitted the signal (the disconnected socket)
    QLocalSocket* clientConnection = qobject_cast<QLocalSocket*>(sender());
    if (clientConnection) {
        qDebug() << "AutomotiveCluster disconnected.";
        m_clients.removeAll(clientConnection);
        clientConnection->deleteLater(); // Safely delete the socket memory
    }
}

void MockCanServer::broadcastVehicleData() {
    // Optimization: Don't do math if no one is listening
    if (m_clients.isEmpty()) return;

    // 1. C++17 <random>: Generate random speed fluctuations
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> speedDist(-2, 3);
    
    m_speed += speedDist(gen);
    if (m_speed < 0) m_speed = 0;
    if (m_speed > 220) m_speed = 220;
    
    m_rpm = 1000 + (m_speed * 30); // Tie RPM to speed for realism

    // 2. Serialization (Preparing data for IPC Network transfer)
    QByteArray block;
    // QDataStream handles Endianness and converts variables to pure bytes
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    
    // We send a complex binary packet: [Speed][RPM][Battery][Gear][TurnSignal][Odo][Range][ADAS]
    out << m_speed << m_rpm << 85 << m_gear << m_turnSignal << m_odometer << m_range << m_adasDistance; 

    // 3. Loop through all connected clients and write the bytes to them
    for (QLocalSocket* client : m_clients) {
        if (client->state() == QLocalSocket::ConnectedState) {
            client->write(block);
            client->flush(); // Force the network buffer to send immediately
        }
    }
}
```

