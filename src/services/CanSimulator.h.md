# src/services/CanSimulator.h - Explanation Guide

**Purpose:** Header for the IPC Client. Defines all the signals needed to transport decoded network data out of the background thread.

### Complete Code & Line-by-Line Explanation

```cpp
#pragma once

#include <QObject>
#include <QThread>
#include <QLocalSocket>
#include <QTimer>
#include <memory> 

class CanSimulator : public QObject {
    Q_OBJECT

public:
    explicit CanSimulator(QObject *parent = nullptr);
    ~CanSimulator() override;

    void startSimulation();
    void stopSimulation();

signals:
    // Emitted across thread boundaries when new IPC data arrives
    void speedReceived(int speed);
    void rpmReceived(int rpm);
    void batterySocReceived(int soc);
    void gearReceived(QString gear);
    void turnSignalReceived(int signal);
    void odometerReceived(int odo);
    void rangeReceived(int range);
    void adasDistanceReceived(int distance);
    void menuIndexReceived(int index);
    void alertMessageReceived(QString message);

private slots:
    void initIpcConnection(); 
    void onReadyRead();       
    void onDisconnected();    

private:
    std::unique_ptr<QThread> m_thread; 
    QLocalSocket* m_socket;            
    QTimer* m_reconnectTimer;          
};
```
