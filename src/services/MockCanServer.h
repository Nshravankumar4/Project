#pragma once

#include <QObject>
#include <QLocalServer>
#include <QLocalSocket>
#include <QTimer>
#include <QList>

// -------------------------------------------------------------
// This class demonstrates: IPC (Local Socket), Multi Threads (Implicit via Event Loop), 
// and Server-Client Architecture required for Automotive Middleware.
// -------------------------------------------------------------
class MockCanServer : public QObject {
    Q_OBJECT
public:
    explicit MockCanServer(QObject *parent = nullptr);
    ~MockCanServer() override;

    bool startServer();

private slots:
    void onNewConnection();
    void onClientDisconnected();
    void broadcastVehicleData(); // Simulates parsing CAN and sending to clients

private:
    QLocalServer* m_server;
    QList<QLocalSocket*> m_clients;
    QTimer* m_timer;

    // Vehicle State
    int m_speed = 0;
    int m_rpm = 1000;
};

