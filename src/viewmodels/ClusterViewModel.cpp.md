# src/viewmodels/ClusterViewModel.cpp - Explanation Guide

**Purpose:** This implements the ViewModel logic. It listens to the background IPC thread, stores the data, and alerts QML when things change.

### Complete Code & Line-by-Line Explanation

```cpp
#include "ClusterViewModel.h"

ClusterViewModel::ClusterViewModel(QObject *parent) 
    : QObject(parent), m_canSimulator(new CanSimulator(nullptr)) 
{
    // 1. Thread-Safe Connections
    // We connect the signals emitted by the background thread (m_canSimulator)
    // to our slots running on the Main GUI Thread. Qt's Event Loop automatically 
    // queues these safely across the thread boundary!
    connect(m_canSimulator, &CanSimulator::speedReceived, this, &ClusterViewModel::onSpeedReceived);
    connect(m_canSimulator, &CanSimulator::rpmReceived, this, &ClusterViewModel::onRpmReceived);
    connect(m_canSimulator, &CanSimulator::batterySocReceived, this, &ClusterViewModel::onBatterySocReceived);

    // 2. Start the background thread for the IPC client
    m_canSimulator->startSimulation();
}

ClusterViewModel::~ClusterViewModel() {
    // 3. Memory Management: Clean up the raw pointer since we didn't give it a parent.
    delete m_canSimulator;
}

// 4. Q_PROPERTY READ functions (Called by QML)
int ClusterViewModel::speed() const { return m_speed; }
int ClusterViewModel::rpm() const { return m_rpm; }
int ClusterViewModel::batterySoc() const { return m_batterySoc; }

// 5. Data handling slots (Called by the background thread via signals)
void ClusterViewModel::onSpeedReceived(int speed) {
    // Optimization: Only update and notify QML if the data actually changed!
    if (m_speed != speed) {
        m_speed = speed;
        emit speedChanged(m_speed); // THIS TELLS QML TO UPDATE THE SCREEN
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
```

