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
    Q_OBJECT
public:
    explicit CanSimulator(QObject *parent = nullptr);
    ~CanSimulator() override;

    void startSimulation();
    void stopSimulation();

signals:
    void speedReceived(int speed);
    void rpmReceived(int rpm);
    void batterySocReceived(int soc);

private slots:
    void initIpcConnection(); // Runs on the background thread
    void onReadyRead();
    void onDisconnected();

private:
    std::unique_ptr<QThread> m_thread;
    QLocalSocket* m_socket;
    QTimer* m_reconnectTimer;
};

