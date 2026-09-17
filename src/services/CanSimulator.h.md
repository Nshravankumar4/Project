# src/services/CanSimulator.h - Explanation Guide

**Purpose:** This class acts as the **IPC Client** for the GUI application. It runs in a background thread and connects to the VehicleService via `QLocalSocket`.

### Complete Code & Line-by-Line Explanation

```cpp
#pragma once

#include <QObject>
#include <QThread>
#include <QLocalSocket>
#include <QTimer>

// -------------------------------------------------------------
// This class demonstrates: IPC Client (Socket), Multi Threads, 
// and C++17 features. It runs in a background QThread to avoid blocking the UI.
// -------------------------------------------------------------
class CanSimulator : public QObject {
    Q_OBJECT // Required macro for any class that uses Qt Signals and Slots
public:
    explicit CanSimulator(QObject *parent = nullptr);
    ~CanSimulator() override;

    void startSimulation();
    void stopSimulation();

signals: // 1. SIGNALS: We declare signals that this class will 'emit' when new data arrives over IPC.
    void speedReceived(int speed);
    void rpmReceived(int rpm);
    void batterySocReceived(int soc);

private slots: // 2. SLOTS: Functions that respond to Qt events (like network data arriving).
    void initIpcConnection(); // Runs on the background thread
    void onReadyRead();       // Triggered when the socket has data to read
    void onDisconnected();    // Triggered if the server crashes

private:
    // 3. Smart Pointers: We use std::unique_ptr for the QThread to ensure memory is 
    // automatically cleaned up without needing 'delete' (RAII pattern).
    std::unique_ptr<QThread> m_thread;
    
    // 4. Raw pointers for Qt objects. In Qt, if you pass a 'parent' (this) to an object, 
    // Qt automatically deletes them when the parent is deleted.
    QLocalSocket* m_socket;
    QTimer* m_reconnectTimer;
};
```

