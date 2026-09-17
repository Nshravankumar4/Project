#include "MockCanServer.h"
#include <QDebug>
#include <QDataStream>
#include <random>

const QString SERVER_NAME = "AutomotiveIpcSocket";

MockCanServer::MockCanServer(QObject *parent) 
    : QObject(parent), m_server(new QLocalServer(this)), m_timer(new QTimer(this)) 
{
    connect(m_server, &QLocalServer::newConnection, this, &MockCanServer::onNewConnection);
    connect(m_timer, &QTimer::timeout, this, &MockCanServer::broadcastVehicleData);
}

MockCanServer::~MockCanServer() {
    m_server->close();
}

bool MockCanServer::startServer() {
    // Remove any existing socket with the same name before starting
    QLocalServer::removeServer(SERVER_NAME);

    if (m_server->listen(SERVER_NAME)) {
        qDebug() << "VehicleService (IPC Server) is running on socket:" << SERVER_NAME;
        m_timer->start(100); // Broadcast data every 100ms
        return true;
    } else {
        qDebug() << "Failed to start IPC Server:" << m_server->errorString();
        return false;
    }
}

void MockCanServer::onNewConnection() {
    QLocalSocket* clientConnection = m_server->nextPendingConnection();
    if (clientConnection) {
        qDebug() << "AutomotiveCluster connected to IPC Server!";
        connect(clientConnection, &QLocalSocket::disconnected, this, &MockCanServer::onClientDisconnected);
        m_clients.append(clientConnection);
    }
}

void MockCanServer::onClientDisconnected() {
    QLocalSocket* clientConnection = qobject_cast<QLocalSocket*>(sender());
    if (clientConnection) {
        qDebug() << "AutomotiveCluster disconnected.";
        m_clients.removeAll(clientConnection);
        clientConnection->deleteLater();
    }
}

void MockCanServer::broadcastVehicleData() {
    if (m_clients.isEmpty()) return;

    // 1. Simulate changing data (like decoding CAN frames)
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> speedDist(-2, 3);
    
    // Simulate speed
    m_speed += speedDist(gen);
    if (m_speed < 0) m_speed = 0;
    if (m_speed > 220) m_speed = 220;
    
    // Simulate RPM
    if (m_speed == 0) {
        m_rpm = 800; // Idle
    } else {
        m_rpm = 1000 + (m_speed * 25) + (speedDist(gen) * 50); 
        if (m_rpm > 7000) m_rpm = 7000;
    }

    // Simulate Gear logic
    if (m_speed > 0) m_gear = "D";
    else m_gear = "P";

    // Simulate Turn signals being active (Turn on left signal when speed is between 40 and 60)
    static int tickCount = 0;
    tickCount++;
    if (m_speed > 40 && m_speed < 60) {
        m_turnSignal = 1; // Left turn signal ON
    } else if (m_speed > 120 && m_speed < 140) {
        m_turnSignal = 2; // Right turn signal ON
    } else {
        m_turnSignal = 0;
    }

    // Simulate ADAS (Distance to car ahead, bounces around)
    std::uniform_int_distribution<> adasDist(-5, 5);
    m_adasDistance += adasDist(gen);
    if (m_adasDistance < 10) m_adasDistance = 10;
    if (m_adasDistance > 150) m_adasDistance = 150;

    // Simulate Steering Wheel Menu buttons being pressed
    if (tickCount % 50 == 0) { // Every 5 seconds, switch the menu
        m_menuIndex = (m_menuIndex + 1) % 4; // 4 info pages total
    }

    // Simulate Alerts (e.g., Door Open, Low Fuel)
    if (m_speed > 100 && tickCount % 40 == 0) {
        m_alertMessage = "SPEED WARNING!";
    } else if (m_range < 50) {
        m_alertMessage = "LOW FUEL!";
    } else {
        m_alertMessage = ""; // No alert
    }

    // 2. Serialize data and broadcast via IPC Socket
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    
    // Binary packet: [Speed][RPM][Battery][Gear][TurnSignal][Odo][Range][ADAS][Menu][Alert]
    out << m_speed << m_rpm << 85 << m_gear << m_turnSignal << m_odometer << m_range << m_adasDistance << m_menuIndex << m_alertMessage; 

    for (QLocalSocket* client : m_clients) {
        if (client->state() == QLocalSocket::ConnectedState) {
            client->write(block);
            client->flush();
        }
    }
}

