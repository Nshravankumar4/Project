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
    
    m_speed += speedDist(gen);
    if (m_speed < 0) m_speed = 0;
    if (m_speed > 220) m_speed = 220;
    
    m_rpm = 1000 + (m_speed * 30); // Rough correlation

    // 2. Serialize data and broadcast via IPC Socket
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    
    // We send a simple binary packet: [Speed (int)][RPM (int)][Battery (int)]
    out << m_speed << m_rpm << 85; 

    for (QLocalSocket* client : m_clients) {
        if (client->state() == QLocalSocket::ConnectedState) {
            client->write(block);
            client->flush();
        }
    }
}

