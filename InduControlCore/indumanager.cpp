#include "indumanager.h"
#include <QDebug>
#include <vector>

//Internal Classes
#include "instrumentmanager.h"
#include "../InduCore/measurementsequence.h"
#include "../InduCore/measseqtc.h"
#include "../InduCore/measseqjc.h"
#include "../InduCore/datapoint.h"
#include "../InduCore/filewriter.h"
#include "../Instruments/ppmsdatapoint.h"



InduManager::InduManager()
    : measurementNumber_(0)
    , instrumentmanager_ (std::make_unique<InstrumentManager>())
    , fw_(nullptr)
    , mSeqTc_(std::make_shared<MeasSeqTc>())
    , mSeqJc_(std::make_shared<MeasSeqJc>())
    , measurementState(State::Idle)
{
    connect(instrumentmanager_.get(), &InstrumentManager::newData,
                this, &InduManager::onNewData);
}

InduManager::~InduManager()
{
}

void InduManager::appendMeasurement(std::vector<std::shared_ptr<const MeasurementSequence> > mVecSeq)
{
    for (const auto mesSeq: mVecSeq)
    {
        mVecSeq_.push_back(mesSeq);
    }

    if(measurementState == State::Idle){
        measurementState = State::CheckForMeas;
        emit newState(measurementState);
    }
}

void InduManager::startMeasurement(std::shared_ptr<const MeasurementSequence> measurementSequence)
{
    auto seqTc = std::dynamic_pointer_cast<const MeasSeqTc> (measurementSequence);
    auto seqJc = std::dynamic_pointer_cast<const MeasSeqJc> (measurementSequence);
    fw_= std::make_unique<FileWriter>();

    fw_->openFile(measurementSequence);
    if(seqTc != nullptr){
        mSeqTc_->setTempStart(seqTc->tempStart());
        mSeqTc_->setTempEnd(seqTc->tempEnd());
        mSeqTc_->setTemperatureRate(seqTc->temperatureRate());
        instrumentmanager_->setTempSetpoint(mSeqTc_->tempStart(), mSeqTc_->temperatureRate());
        measurementState= State::ApproachStartTc;
        emit newState(measurementState);
    }
    if(seqJc != nullptr){
        mSeqJc_->setVoltStart(seqJc->voltStart());

    }
}
/* NOTE
 * Grundsätzlich findet vieles deiner Prozesslogik hier im Switch-Statement statt,
 * mit Ausnahme des "Start Measurement"-Algorithmus.
 * Ich würde es sinnvoller finden, lieber noch einen weiteren State zu definieren, sowas wie
 * "setStartSetpoints" oder "StartMeasurement" (der Methodenname von oben) und dann den Algorithmus
 * auch im switch-Statement auszuführen. Dann ist alles, was für "Start/Stop/Warte/Speicher in Datei"
 * notwendig ist, hier an einer Stelle.
 */
void InduManager::onNewData(std::shared_ptr<DataPoint> datapoint)
{
    emit newData(datapoint);

    switch (measurementState)
    {
    case State::Idle:{
            //NOTE if abfrage-> ob das Programm bei Aktueller Temp bleiben soll, oder Energiesparmodus!
            break;
        }
    case State::ApproachStartTc:{
            if(std::abs(mSeqTc_->tempStart() - datapoint->ppmsdata()->pvTempLive()) < 0.1)
            {
                measurementState = State::ApproachEndTc;
                instrumentmanager_->setTempSetpoint(mSeqTc_->tempEnd(), mSeqTc_->temperatureRate());
            }
            break;
        }
    case State::ApproachEndTc:{
           if(fw_!= nullptr){
                fw_->append(datapoint);
           }

           if(std::abs(mSeqTc_->tempEnd() - datapoint->ppmsdata()->pvTempLive()) < 0.1)
           {
                fw_->closeFile();
                measurementState = State::CheckForMeas;
                measurementNumber_++;
           }
            break;
        }
    case State::CheckForMeas:{
            if(mVecSeq_.size()> measurementNumber_ )
            {
                emit startNewMeasurement(mVecSeq_[measurementNumber_]);
            }
            else{
                measurementState = State::Idle;
            }
            break;
        }

    default:assert(false);
    }
    emit newState(measurementState);
}


