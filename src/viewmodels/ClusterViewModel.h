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

public:
    explicit ClusterViewModel(QObject *parent = nullptr);
    ~ClusterViewModel() override;

    // Getters for Q_PROPERTY
    int speed() const;
    int rpm() const;
    int batterySoc() const;

signals:
    // NOTIFY signals for Q_PROPERTY
    void speedChanged(int speed);
    void rpmChanged(int rpm);
    void batterySocChanged(int soc);

private slots:
    // Slots to receive data from the CanSimulator thread
    void onSpeedReceived(int speed);
    void onRpmReceived(int rpm);
    void onBatterySocReceived(int soc);

private:
    int m_speed = 0;
    int m_rpm = 0;
    int m_batterySoc = 100;
    
    CanSimulator* m_canSimulator;
};

