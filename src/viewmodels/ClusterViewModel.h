#pragma once

#include <QObject>
#include "../services/CanSimulator.h"

// The ClusterViewModel acts as the "ViewModel" in the MVVM pattern.
// It exposes C++ data to QML via Q_PROPERTY, serving as the bridge between
// the backend business logic (CanSimulator/VehicleData) and the Frontend (QML).
class ClusterViewModel : public QObject {
    Q_OBJECT

    // Q_PROPERTY allows QML to read/write properties and be notified when they change
    Q_PROPERTY(int speed READ speed NOTIFY speedChanged)
    Q_PROPERTY(int rpm READ rpm NOTIFY rpmChanged)
    Q_PROPERTY(int batterySoc READ batterySoc NOTIFY batterySocChanged)
    Q_PROPERTY(QString gear READ gear NOTIFY gearChanged)
    Q_PROPERTY(int turnSignal READ turnSignal NOTIFY turnSignalChanged)
    Q_PROPERTY(int odometer READ odometer WRITE setOdometer NOTIFY odometerChanged)
    Q_PROPERTY(int range READ range NOTIFY rangeChanged)
    Q_PROPERTY(int adasDistance READ adasDistance NOTIFY adasDistanceChanged)
    Q_PROPERTY(int menuIndex READ menuIndex WRITE setMenuIndex NOTIFY menuIndexChanged)
    Q_PROPERTY(QString alertMessage READ alertMessage NOTIFY alertMessageChanged)

public:
    explicit ClusterViewModel(QObject *parent = nullptr);
    ~ClusterViewModel() override;

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

    void setMenuIndex(int index);
    void setOdometer(int odo);

signals:
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

