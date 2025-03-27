#include "display.h"
#include <QApplication>
#include <QMouseEvent>
#include "Path.h"

using namespace std;



ImageWidget::ImageWidget(Pixel **externalData, int width, int height, QWidget *parent)
    : QWidget(parent), data(externalData), width(width), height(height) {
    setWindowTitle("bitmap");
    resize(400, 400);

    imageLabel = new QLabel(this);
    imageLabel->setScaledContents(true);
    imageLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(imageLabel);
    setLayout(layout);

    updateImage();
}

void ImageWidget::refreshDisplay() { updateImage(); }

void ImageWidget::updateImage() {
    QImage image(width, height, QImage::Format_RGB32);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int c =(data[x][y].black)?0 :255;
            image.setPixel(y, x, qRgb(c,c,c));
        }
    }
    imageLabel->setPixmap(QPixmap::fromImage(image));
}

void ImageWidget::mousePressEvent(QMouseEvent *event) {
    QPoint pos = event->pos();
    int x = (pos.x()-10)*width/imageLabel->width();
    int y = (pos.y()-10)*height/imageLabel->height();
    if (x >= 0 && x < width && y >= 0 && y < height) {
    delete CurrentStroke;
    CurrentStroke = new shape(x,y);
    modifyPixel(x,y);
    x0=x;
    y0=y;
    }
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event) {
    QPoint pos = event->pos();
    int x = (pos.x()-10)*width/imageLabel->width();
    int y = (pos.y()-10)*height/imageLabel->height();
    if (x >= 0 && x < width && y >= 0 && y < height) {
    if (event->buttons() & Qt::LeftButton) {
        CurrentStroke->add(x,y);
        modifyPixel(x,y);
    }
    }
}

void ImageWidget::connectPixel(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while ((x1 != x2) || (y1 != y2)) {
        if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height) {
            data[y1][x1].black = true;
        }
        int e2 = err * 2;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }

    if (x2 >= 0 && x2 < width && y2 >= 0 && y2 < height) {
        data[y2][x2].black = true;
    }

    updateImage();
}


void ImageWidget::clearBitmap(){
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            data[y][x].black = false;
        }
    }}

void ImageWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return) {
        clearBitmap();
        CurrentStroke->SimplifyPath();
        CurrentStroke->Interpolation();
        CurrentStroke->applyFFT();
        emit shapeReady(CurrentStroke);
        for (int i = 0; i < CurrentStroke->N; i++) {
        }

        Path* current = CurrentStroke->start;
        while (current && current->next) {
            data[current->y][current->x].black = true;
            connectPixel(current->x, current->y, current->next->x, current->next->y);
            current= current->next;
        }

        updateImage();
    }
}

void ImageWidget::modifyPixel(int x,int y) {
        if (eraser){
            data[y][x].black = false;
        }
        if (!eraser){
            if (!data[y][x].black){
                data[y][x].black = true;
                }
    }

    updateImage();
    }





