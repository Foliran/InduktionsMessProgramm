#ifndef PPPMSWIDGET_H
#define PPPMSWIDGET_H

#include <QWidget>

class DataPoint;
class QLabel;

class PpmsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PpmsWidget(QWidget *parent = nullptr);


    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    void newData(std::shared_ptr<const DataPoint> dpoint);

private:
    void setupUI();

    //tempBlock
    QLabel* tempSetPoint_;
    QLabel* tempLive_;
    QLabel* tempRate_;
    QLabel* tempStatus_;

    //MagBlock
    QLabel* magSetPoint_;
    QLabel* magFieldLive_;
    QLabel* magStatus_;

    //RotationBlock
    QLabel* rotSetPoint_;
    QLabel* rotLive_;
    QLabel* rotStatus_;

    //Chamber
    QLabel* chamberStatus_;
    QLabel* chamberLevel_;


};

#endif // PPPMSWIDGET_H