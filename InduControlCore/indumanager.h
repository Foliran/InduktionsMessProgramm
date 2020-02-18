#ifndef INDUMANAGER_H
#define INDUMANAGER_H
#include "InduControlCore_global.h"
#include <memory>
#include <QObject>



//forward
class PpmsSimulation;
class MeasSeqTc;
class MeasurementSequence;
class DataPoint;
class FileWriter;
class InstrumentManager;


class INDUCONTROLCORE_EXPORT InduManager :public QObject
{
    Q_OBJECT

signals:
    void newData(std::shared_ptr<const DataPoint>);
public:
    explicit InduManager();
    ~InduManager();
    enum class State { Idle, ApproachStart, ApproachEnd};
    void startMeasurement(std::shared_ptr<const MeasurementSequence> &measurementSequence);

    State getMeasurementState() const;

private slots:
    std::shared_ptr<DataPoint> onNewData(std::shared_ptr<DataPoint> datapoint);

private:
    InstrumentManager *instrumentmanager_;
    std::unique_ptr <FileWriter> fw_;
    bool setPointStand;
    std::shared_ptr <MeasSeqTc> mSeqTc_;

    State measurementState;

};

#endif // INDUMANAGER_H
