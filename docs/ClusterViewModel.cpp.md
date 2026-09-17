# src/viewmodels/ClusterViewModel.cpp - Explanation Guide

**Purpose:** Implements the MVVM bridge between the C++ backend and QML frontend.

### Complete Code & Line-by-Line Explanation

```cpp
#include "ClusterViewModel.h"
#include "../utils/Logger.h" // Import our Singleton

ClusterViewModel::ClusterViewModel(QObject *parent) 
    : QObject(parent), m_canSimulator(new CanSimulator(nullptr)) 
{
    // CROSS-THREAD CONNECTION:
    // Safely connects the background IPC thread to the Main GUI Thread.
    connect(m_canSimulator, &CanSimulator::speedReceived, this, &ClusterViewModel::onSpeedReceived);
    connect(m_canSimulator, &CanSimulator::rpmReceived, this, &ClusterViewModel::onRpmReceived);
    // ... (other connects)
    
    m_canSimulator->startSimulation();
}

ClusterViewModel::~ClusterViewModel() {
    delete m_canSimulator;
}

// ---------------------------------------------------------
// GETTERS (QML calls these via Q_PROPERTY READ)
// ---------------------------------------------------------
int ClusterViewModel::speed() const { return m_speed; }
int ClusterViewModel::odometer() const { return m_odometer; }
// ... (other getters)

// ---------------------------------------------------------
// SETTERS (QML calls these via Q_PROPERTY WRITE)
// ---------------------------------------------------------
void ClusterViewModel::setMenuIndex(int index) {
    if (m_menuIndex != index) {
        m_menuIndex = index;
        // USING THE SINGLETON OBSERVER:
        Logger::getInstance().log("Menu Index changed to: " + QString::number(index));
        emit menuIndexChanged(m_menuIndex);
    }
}

void ClusterViewModel::setOdometer(int odo) {
    if (m_odometer != odo) {
        m_odometer = odo;
        Logger::getInstance().log("Odometer manually reset to: " + QString::number(odo));
        emit odometerChanged(m_odometer);
    }
}

// ---------------------------------------------------------
// SLOTS (Receives data from Background IPC)
// ---------------------------------------------------------
void ClusterViewModel::onSpeedReceived(int speed) {
    if (m_speed != speed) {     
        m_speed = speed;
        emit speedChanged(m_speed); // Repaints the UI!
    }
}
```
