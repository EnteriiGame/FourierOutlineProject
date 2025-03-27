#ifndef VECTORDISPLAY_H
#define VECTORDISPLAY_H

#include "Path.h"
#include <QWidget>
#include <QTimer>

class VectorDisplay : public QWidget {
    Q_OBJECT
public:
    explicit VectorDisplay(QWidget *parent = nullptr);
    ~VectorDisplay();
    void setFC(RotatorCoeficients& trace);//fourier Coefficients
protected:
    void paintEvent(QPaintEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private:
    void updateAnimation();
    RotatorCoeficients traces;
    double time;
    QTimer* timer;
    std::vector<QPointF> tracePoints;
};

#endif // VECTORDISPLAY_H
