#include "VectorDisplay.h"
#include <QPainter>
#include <cmath>

int TraceLength = 100;
double speedM = 20;
double speed=1;

VectorDisplay::VectorDisplay(QWidget *parent) : QWidget(parent), time(0) {
    setWindowTitle("Fourier Vector Animation");
    resize(600, 600);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &VectorDisplay::updateAnimation);
    timer->start(10);
}

void VectorDisplay::setFC(RotatorCoeficients& trace) {
    traces = trace;
}

void VectorDisplay::updateAnimation() {
    time += 0.01;
    update();
}

VectorDisplay::~VectorDisplay() {
    if (timer) {
        timer->stop();
        delete timer;
        timer = nullptr;
    }
}

void VectorDisplay::closeEvent(QCloseEvent *event) {
    if (timer) {
        timer->stop();
        delete timer;
        timer = nullptr;
    }
}

void VectorDisplay::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    Complex sum(0, 0);
    Complex prev(0, 0);
    float scale = .05;
    speedM = speedM/(traces.N/2-1);

    for (size_t k = 0; k< traces.N; ++k) {
        double freq;
        if ((k==0)||(k==traces.N/2)){freq=.0f;}
        else if(k<traces.N/2){freq = float(k);}
        else freq=float((traces.N)-k)*(-1);


        Complex rotatingVector = traces.C[k];
        rotatingVector *= ComplexExp((freq*time*PI)/speed);
        sum += rotatingVector;

        painter.setPen(Qt::black);
        painter.drawLine(prev.rel * scale, prev.img * scale, sum.rel * scale, sum.img * scale);
        prev = sum;
    }



    QPointF newPoint(sum.rel * scale, sum.img * scale);
    tracePoints.push_back(newPoint);
    if (tracePoints.size() > TraceLength) {
        tracePoints.erase(tracePoints.begin());
    }


    for (size_t i = 0; i < tracePoints.size()-1; ++i) {
        int alpha = 255 * (i + 1) / tracePoints.size();
        painter.setPen(QColor(0, 0, 255, alpha));
        painter.drawLine(tracePoints[i],tracePoints[i+1]);
    }

    painter.setPen(Qt::red);
    painter.drawEllipse(newPoint, 3, 3);
}
