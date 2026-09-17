#include "CanSimulator.h"
#include <QDataStream>
#include <QDebug>

const QString SERVER_NAME = "AutomotiveIpcSocket";

CanSimulator::CanSimulator(QObject *parent) 
    : QObject(parent), m_thread(std::make_unique<QThread>()), m_socket(nullptr), m_reconnectTimer(nullptr)
{
    // ------------------------------------------------------------------
    // MULTITHREADING: We move this object to a background thread.
    // This ensures that slow IPC/Network operations do NOT block the QML UI.
    // ------------------------------------------------------------------
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
    // Objects created inside this method live on the background thread
    m_socket = new QLocalSocket(this);
    m_reconnectTimer = new QTimer(this);

    connect(m_socket, &QLocalSocket::readyRead, this, &CanSimulator::onReadyRead);
    connect(m_socket, &QLocalSocket::disconnected, this, &CanSimulator::onDisconnected);
    
    connect(m_reconnectTimer, &QTimer::timeout, this, [this]() {
        if (m_socket->state() == QLocalSocket::UnconnectedState) {
            m_socket->connectToServer(SERVER_NAME);
        }
    });

    m_reconnectTimer->start(1000); // Try connecting every 1 second
    m_socket->connectToServer(SERVER_NAME);
}

void CanSimulator::onDisconnected() {
    qDebug() << "Lost connection to VehicleService. Attempting to reconnect...";
}

void CanSimulator::onReadyRead() {
    QDataStream in(m_socket);
    in.setVersion(QDataStream::Qt_6_0);

    // Read available data from the IPC socket
    while (!in.atEnd()) {
        int speed = 0, rpm = 0, batterySoc = 0, turnSignal = 0, odometer = 0, range = 0, adasDistance = 0, menuIndex = 0;
        QString gear, alertMessage;
        
        in >> speed >> rpm >> batterySoc >> gear >> turnSignal >> odometer >> range >> adasDistance >> menuIndex >> alertMessage;

        // Bridge to the ViewModel (Cross-thread signal emission)
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

