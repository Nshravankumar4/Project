# src/viewmodels/ClusterViewModel.h - Explanation Guide

**Purpose:** The ViewModel in the MVVM pattern. It sits strictly on the Main GUI Thread, exposing Q_PROPERTY variables so QML can bind to them securely without knowing about networking or multithreading.

### Complete Code & Line-by-Line Explanation

```cpp
#pragma once

#include <QObject>
#include "../services/CanSimulator.h"

class ClusterViewModel : public QObject {
    Q_OBJECT

    // Q_PROPERTY macros tell the QML Engine that these variables exist
    // and which SIGNAL to listen to when they change.
    Q_PROPERTY(int speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(int rpm READ rpm NOTIFY rpmChanged)
    Q_PROPERTY(int batterySoc READ batterySoc NOTIFY batterySocChanged)
    Q_PROPERTY(QString gear READ gear NOTIFY gearChanged)
    Q_PROPERTY(int turnSignal READ turnSignal NOTIFY turnSignalChanged)
    Q_PROPERTY(int odometer READ odometer NOTIFY odometerChanged)
    Q_PROPERTY(int range READ range NOTIFY rangeChanged)
    Q_PROPERTY(int adasDistance READ adasDistance NOTIFY adasDistanceChanged)
    
    // WRITE allows QML to push changes back to C++ (Used for Touch Events!)
    Q_PROPERTY(int menuIndex READ menuIndex WRITE setMenuIndex NOTIFY menuIndexChanged)
    Q_PROPERTY(QString alertMessage READ alertMessage NOTIFY alertMessageChanged)

public:
    explicit ClusterViewModel(QObject *parent = nullptr);
    ~ClusterViewModel() override;

    // Getters
    int speed() const;
    int rpm() const;
    int batterySoc() const;
    QString gear() const;
    int turnSignal() const;
    int odometer() const;
    int range() const;
    int adasDistance() const;
    int menuIndex() const;
    QString alertMessage() const;

    // Setters
    void setMenuIndex(int index);

signals:
    // QML Engine hooks into these to auto-update the UI
    void speedChanged(int speed);
    void rpmChanged(int rpm);
    void batterySocChanged(int soc);
    void gearChanged(QString gear);
    void turnSignalChanged(int signal);
    void odometerChanged(int odo);
    void rangeChanged(int range);
    void adasDistanceChanged(int distance);
    void menuIndexChanged(int index);
    void alertMessageChanged(QString message);

private slots:
    // Slots that capture signals sent by the CanSimulator background thread
    void onSpeedReceived(int speed);
    void onRpmReceived(int rpm);
    void onBatterySocReceived(int soc);
    void onGearReceived(QString gear);
    void onTurnSignalReceived(int signal);
    void onOdometerReceived(int odo);
    void onRangeReceived(int range);
    void onAdasDistanceReceived(int distance);
    void onMenuIndexReceived(int index);
    void onAlertMessageReceived(QString message);

private:
    int m_speed = 0;
    int m_rpm = 0;
    int m_batterySoc = 100;
    QString m_gear = "P";
    int m_turnSignal = 0;
    int m_odometer = 0;
    int m_range = 0;
    int m_adasDistance = 100;
    int m_menuIndex = 0;
    QString m_alertMessage = "";
    
    CanSimulator* m_canSimulator;
};
```
