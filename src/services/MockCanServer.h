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
    QString m_gear = "P";
    int m_turnSignal = 0; // 0=off, 1=left, 2=right
    int m_odometer = 15420;
    int m_range = 450;
    int m_adasDistance = 100;
    
    // New features for Info Pages and Alerts
    int m_menuIndex = 0;
    QString m_alertMessage = "";
};

