#include "instrumentmanager.h"
#include <QDebug>
#include <QRandomGenerator>

//Internal Classes
#include "../InduCore/datapoint.h"
#include "../Instruments/ppmssimulation.h"
#include "../Instruments/lockinsimulation.h"

InstrumentManager::InstrumentManager()
    : timer_(new QTimer(this))
    , ppmssimu_(std::make_shared<PpmsSimulation>())
    , lockinsimu_(std::make_shared<LockInSimulation>())
{
    connect(timer_, &QTimer::timeout, this, &InstrumentManager::onPolling);
    timer_->start(200);
}

void InstrumentManager::setTempSetpoint(double setpoint, double rate)
{
    ppmssimu_->setTempSetpoint(setpoint, rate);
}


void InstrumentManager::onPolling()
{
    auto dataPoint = ppmssimu_->generateVariables();
    /*TODO:
    *   dataPoint = lockinsimu_->lockInLogik();
    *   Irgendwie müssen die daten von lockinSimu hinzugefügt werden.
    */
    emit newData(dataPoint);
}
