# src/services/MockCanServer.h - Explanation Guide

**Purpose:** Defines the IPC Server class that acts as the physical vehicle broadcasting CAN data.

### Complete Code & Line-by-Line Explanation

```cpp
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
    Q_OBJECT // Required for signals/slots

public:
    explicit MockCanServer(QObject *parent = nullptr);
    ~MockCanServer() override;

    bool startServer(); // Opens the IPC socket

private slots:
    // Slots that react to Qt Network events
    void onNewConnection();
    void onClientDisconnected();
    
    // Slot triggered by a timer to generate fake CAN data
    void broadcastVehicleData(); 

private:
    // QLocalServer is the Qt class for Local IPC (Inter-Process Communication)
    QLocalServer* m_server;
    
    // A list of all connected dashboards (QLocalSocket pointers)
    QList<QLocalSocket*> m_clients;
    
    // Timer to trigger data generation
    QTimer* m_timer;

    // Vehicle State
    int m_speed = 0;
    int m_rpm = 1000;
};
```

