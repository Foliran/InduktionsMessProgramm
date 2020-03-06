#ifndef LOCKINSR830_H
#define LOCKINSR830_H

#include "Instruments_global.h"
#include <QObject>
#include <memory>

//Internal Classes
#include "../InduCore/datapoint.h"
#include "lockindatapoint.h"

class INSTRUMENTS_EXPORT LockInSr830 : public QObject
{
    Q_OBJECT
public:
    LockInSr830();
    void setInputVoltage(double InputVoltage);
    void setFreq(double freq);
    void setSensivity(int sensivity);
    void setHarmonic(int harmonicW);
signals:
    void newFreqSP(double freq);
    void newSensivitySP(int sensivity);
    void newHarmonicSP(int harmonicW);
public slots:
    LockInDataPoint lockInLogik();
private:
    DataPoint datapoint_;
    double inputVoltage_;
    double voltnow_;
    double freq_;
    double sensivity_;
    double harmonicW_;
    double phase_;
};

#endif