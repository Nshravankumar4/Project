# src/viewmodels/ClusterViewModel.cpp - Explanation Guide

**Purpose:** Implements the connection between the background IPC thread and the QML Frontend.

### Complete Code & Line-by-Line Explanation

```cpp
#include "ClusterViewModel.h"

ClusterViewModel::ClusterViewModel(QObject *parent) 
    : QObject(parent), m_canSimulator(new CanSimulator(nullptr)) 
{
    // CROSS-THREAD CONNECTION:
    // Because CanSimulator lives on a QThread and ClusterViewModel lives on the Main Thread,
    // Qt automatically uses a QueuedConnection. This means signals are safely pushed into
    // the Main Thread's Event Loop, completely preventing threading crashes!
    connect(m_canSimulator, &CanSimulator::speedReceived, this, &ClusterViewModel::onSpeedReceived);
    connect(m_canSimulator, &CanSimulator::rpmReceived, this, &ClusterViewModel::onRpmReceived);
    connect(m_canSimulator, &CanSimulator::batterySocReceived, this, &ClusterViewModel::onBatterySocReceived);
    connect(m_canSimulator, &CanSimulator::gearReceived, this, &ClusterViewModel::onGearReceived);
    connect(m_canSimulator, &CanSimulator::turnSignalReceived, this, &ClusterViewModel::onTurnSignalReceived);
    connect(m_canSimulator, &CanSimulator::odometerReceived, this, &ClusterViewModel::onOdometerReceived);
    connect(m_canSimulator, &CanSimulator::rangeReceived, this, &ClusterViewModel::onRangeReceived);
    connect(m_canSimulator, &CanSimulator::adasDistanceReceived, this, &ClusterViewModel::onAdasDistanceReceived);
    connect(m_canSimulator, &CanSimulator::menuIndexReceived, this, &ClusterViewModel::onMenuIndexReceived);
    connect(m_canSimulator, &CanSimulator::alertMessageReceived, this, &ClusterViewModel::onAlertMessageReceived);

    m_canSimulator->startSimulation();
}

ClusterViewModel::~ClusterViewModel() {
    delete m_canSimulator;
}

// ---------------------------------------------------------
// GETTERS (QML calls these automatically via Q_PROPERTY)
// ---------------------------------------------------------
int ClusterViewModel::speed() const { return m_speed; }
int ClusterViewModel::rpm() const { return m_rpm; }
int ClusterViewModel::batterySoc() const { return m_batterySoc; }
QString ClusterViewModel::gear() const { return m_gear; }
int ClusterViewModel::turnSignal() const { return m_turnSignal; }
int ClusterViewModel::odometer() const { return m_odometer; }
int ClusterViewModel::range() const { return m_range; }
int ClusterViewModel::adasDistance() const { return m_adasDistance; }
int ClusterViewModel::menuIndex() const { return m_menuIndex; }
QString ClusterViewModel::alertMessage() const { return m_alertMessage; }

// ---------------------------------------------------------
// SETTERS (Allows QML Touch Events to modify C++ state)
// ---------------------------------------------------------
void ClusterViewModel::setMenuIndex(int index) {
    if (m_menuIndex != index) {
        m_menuIndex = index;
        emit menuIndexChanged(m_menuIndex);
    }
}

// ---------------------------------------------------------
// SLOTS (Receives data from Background Thread)
// ---------------------------------------------------------
void ClusterViewModel::onSpeedReceived(int speed) {
    if (m_speed != speed) {     // Prevent duplicate emissions
        m_speed = speed;
        emit speedChanged(m_speed); // Tells QML to repaint the screen
    }
}
// (Other slots follow the exact same pattern...)
```
