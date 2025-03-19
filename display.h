#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QImage>
#include <QPixmap>
#include <QMouseEvent>
#include <QKeyEvent>
#include "Path.h"



struct Pixel {
    bool black=false;
};

class ImageWidget : public QWidget {
    Q_OBJECT

public:
    ImageWidget(Pixel **externalData, int width, int height, QWidget *parent = nullptr);
    void refreshDisplay();
    bool eraser = false;
    shape* CurrentStroke=new shape(0,0);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    //void keyReleaseEvent(QKeyEvent *event);

private:
    void updateImage();
    void clearBitmap();
    void modifyPixel(int x, int y);
    void connectPixel(int x, int y, int i, int j);

    Pixel **data;
    int width, height;
    QLabel *imageLabel;
    int x0, y0;// last position of the dot
};

#endif // DISPLAY_H
