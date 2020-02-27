#ifndef INSTRUMENTMANAGER_H                          //Aufgabe: Daten von Messequence an PPMS-Core UND GBIB-Core weiter zu geben!
#define INSTRUMENTMANAGER_H
#include "InduControlCore_global.h"
#include <memory>
#include <QTimer>

//Internal Classes
#include "../InduCore/datapoint.h"
class QObject;
class PpmsSimulation;
class LockInSimulation;
class MeasSeqTc;

class INDUCONTROLCORE_EXPORT InstrumentManager: public QObject
{
    Q_OBJECT
signals:
    void newData(std::shared_ptr<DataPoint> dataPoint);
public:
    InstrumentManager();
    ~InstrumentManager()=default;
    void setTempSetpoint(double setpoint, double rate);
    void SetInputVoltage(double InputVoltage);

private slots:
    void onPolling();

private:
    QTimer* timer_;
    std::shared_ptr<PpmsSimulation> ppmssimu_;
    std::shared_ptr<LockInSimulation> lockinsimu_ ;
};

#endif // INSTRUMENTMANAGER_H

