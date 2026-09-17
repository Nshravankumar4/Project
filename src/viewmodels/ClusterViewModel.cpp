#include "ClusterViewModel.h"

ClusterViewModel::ClusterViewModel(QObject *parent) 
    : QObject(parent), m_canSimulator(new CanSimulator(nullptr)) 
{
    // Connect the background simulator signals to our slots
    // This is cross-thread communication handled safely by Qt's event loop
    connect(m_canSimulator, &CanSimulator::speedReceived, this, &ClusterViewModel::onSpeedReceived);
    connect(m_canSimulator, &CanSimulator::rpmReceived, this, &ClusterViewModel::onRpmReceived);
    connect(m_canSimulator, &CanSimulator::batterySocReceived, this, &ClusterViewModel::onBatterySocReceived);

    // Start the CAN simulation thread
    m_canSimulator->startSimulation();
}

ClusterViewModel::~ClusterViewModel() {
    delete m_canSimulator;
}

int ClusterViewModel::speed() const {
    return m_speed;
}

int ClusterViewModel::rpm() const {
    return m_rpm;
}

int ClusterViewModel::batterySoc() const {
    return m_batterySoc;
}

void ClusterViewModel::onSpeedReceived(int speed) {
    if (m_speed != speed) {
        m_speed = speed;
        emit speedChanged(m_speed); // Notifies QML that the value changed
    }
}

void ClusterViewModel::onRpmReceived(int rpm) {
    if (m_rpm != rpm) {
        m_rpm = rpm;
        emit rpmChanged(m_rpm);
    }
}

void ClusterViewModel::onBatterySocReceived(int soc) {
    if (m_batterySoc != soc) {
        m_batterySoc = soc;
        emit batterySocChanged(m_batterySoc);
    }
}

