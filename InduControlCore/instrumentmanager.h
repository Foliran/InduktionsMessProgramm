#ifndef INSTRUMENTMANAGER_H
#define INSTRUMENTMANAGER_H
/*Aufgabe: Daten von Messequence an PPMS-Core
 * & GBIB-Core weiter zu geben!
 */
#include "InduControlCore_global.h"
#include <memory>
#include <QTimer>

//Internal Classes
#include "../InduCore/datapoint.h"
class PpmsAbstract;
class LockInAbstract;
class GPIB;


class INDUCONTROLCORE_EXPORT InstrumentManager : public QObject
{
    Q_OBJECT

signals:
    void newData(std::shared_ptr<DataPoint> dataPoint);
    void newTempSP(double setpoint, double rate);
    void newMagSP(double magField, double magRate);
    void newAngleSP(double angle);
    void newFreqSP(double freq);
    void newSensivitySP(int sensivity);
    void newHarmonicSP(int harmonicW);
public:
    InstrumentManager();
    ~InstrumentManager() = default;
    void setTempSetpoint(double setpoint, double rate);
    void setInputVoltage(double inputVoltage);
    void setMagFieldSP(double magField, double magRate);
    void setAngle(double angle);
    void setFrequency(double freq);
    void setSensivity(int sensivity);
    void setHarmonic(double harmonic);

private slots:
    void onPolling();

private:
    QTimer* timer_;
    bool simulation_ = true;
    PpmsAbstract *ppms_;
    LockInAbstract *lockin_;
    std::shared_ptr <GPIB> gpib_;
};

#endif // INSTRUMENTMANAGER_H

