# src/viewmodels/ClusterViewModel.h - Explanation Guide

**Purpose:** This file defines the **ViewModel** in the MVVM architecture. It acts as the bridge between the raw C++ backend data (IPC) and the QML Frontend UI.

### Complete Code & Line-by-Line Explanation

```cpp
#pragma once

#include <QObject>
#include "../services/CanSimulator.h"

// The ClusterViewModel acts as the "ViewModel" in the MVVM pattern.
// It exposes C++ data to QML via Q_PROPERTY.
class ClusterViewModel : public QObject {
    Q_OBJECT

    // 1. Q_PROPERTY (CRUCIAL FOR INTERVIEWS)
    // This tells the QML Engine that this C++ object has a property called "speed".
    // READ speed: When QML asks for the speed, call the C++ function speed().
    // NOTIFY speedChanged: When the speed changes in C++, we promise to emit speedChanged() 
    // so QML knows to update the UI on the screen instantly.
    Q_PROPERTY(int speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(int rpm READ rpm NOTIFY rpmChanged)
    Q_PROPERTY(int batterySoc READ batterySoc NOTIFY batterySocChanged)

public:
    explicit ClusterViewModel(QObject *parent = nullptr);
    ~ClusterViewModel() override;

    // 2. Getters: These are the READ functions defined in the Q_PROPERTY macros above.
    int speed() const;
    int rpm() const;
    int batterySoc() const;

signals:
    // 3. NOTIFY signals: These are emitted to tell QML that data has changed.
    void speedChanged(int speed);
    void rpmChanged(int rpm);
    void batterySocChanged(int soc);

private slots:
    // 4. Slots to receive the raw data coming from the CanSimulator's background thread
    void onSpeedReceived(int speed);
    void onRpmReceived(int rpm);
    void onBatterySocReceived(int soc);

private:
    int m_speed = 0;
    int m_rpm = 0;
    int m_batterySoc = 100;
    
    CanSimulator* m_canSimulator;
};
```

