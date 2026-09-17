#include "ClusterViewModel.h"

ClusterViewModel::ClusterViewModel(QObject *parent) 
    : QObject(parent), m_canSimulator(new CanSimulator(nullptr)) 
{
    // Connect signals safely across threads
    connect(m_canSimulator, &CanSimulator::speedReceived, this, &ClusterViewModel::onSpeedReceived);
    connect(m_canSimulator, &CanSimulator::rpmReceived, this, &ClusterViewModel::onRpmReceived);
    connect(m_canSimulator, &CanSimulator::batterySocReceived, this, &ClusterViewModel::onBatterySocReceived);
    connect(m_canSimulator, &CanSimulator::gearReceived, this, &ClusterViewModel::onGearReceived);
    connect(m_canSimulator, &CanSimulator::turnSignalReceived, this, &ClusterViewModel::onTurnSignalReceived);
    connect(m_canSimulator, &CanSimulator::odometerReceived, this, &ClusterViewModel::onOdometerReceived);
    connect(m_canSimulator, &CanSimulator::rangeReceived, this, &ClusterViewModel::onRangeReceived);
    connect(m_canSimulator, &CanSimulator::adasDistanceReceived, this, &ClusterViewModel::onAdasDistanceReceived);

    m_canSimulator->startSimulation();
}

ClusterViewModel::~ClusterViewModel() {
    delete m_canSimulator;
}

// Getters
int ClusterViewModel::speed() const { return m_speed; }
int ClusterViewModel::rpm() const { return m_rpm; }
int ClusterViewModel::batterySoc() const { return m_batterySoc; }
QString ClusterViewModel::gear() const { return m_gear; }
int ClusterViewModel::turnSignal() const { return m_turnSignal; }
int ClusterViewModel::odometer() const { return m_odometer; }
int ClusterViewModel::range() const { return m_range; }
int ClusterViewModel::adasDistance() const { return m_adasDistance; }

void ClusterViewModel::onSpeedReceived(int speed) {
    if (m_speed != speed) {
        m_speed = speed;
        emit speedChanged(m_speed);
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

void ClusterViewModel::onGearReceived(QString gear) {
    if (m_gear != gear) {
        m_gear = gear;
        emit gearChanged(m_gear);
    }
}

void ClusterViewModel::onTurnSignalReceived(int signal) {
    if (m_turnSignal != signal) {
        m_turnSignal = signal;
        emit turnSignalChanged(m_turnSignal);
    }
}

void ClusterViewModel::onOdometerReceived(int odo) {
    if (m_odometer != odo) {
        m_odometer = odo;
        emit odometerChanged(m_odometer);
    }
}

void ClusterViewModel::onRangeReceived(int range) {
    if (m_range != range) {
        m_range = range;
        emit rangeChanged(m_range);
    }
}

void ClusterViewModel::onAdasDistanceReceived(int distance) {
    if (m_adasDistance != distance) {
        m_adasDistance = distance;
        emit adasDistanceChanged(m_adasDistance);
    }
}
