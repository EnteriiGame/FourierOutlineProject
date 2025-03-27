 /*
#include "display.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    int width = 100, height = 100;
    Pixel **data = new Pixel*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new Pixel[width]{}; // Initialize all pixels to default (black)
    }

    ImageWidget widget(data, width, height);
    widget.show();

    int result = app.exec();

    // Clean up dynamically allocated memory
    for (int i = 0; i < height; ++i) {
        delete[] data[i];
    }
    delete[] data;

    return result;
}// */
 /*
#include <QApplication>
#include "VectorDisplay.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Example Fourier coefficients (from FFT output)
     RotatorCoeficients *curve = new RotatorCoeficients();
    curve->setN(5);
    curve->C[0] = Complex(10,4);
    curve->C[1] = Complex(30,4);
    curve->C[2] = Complex(20,5);
    curve->C[3] = Complex(5,4);
    curve->C[4] = Complex(14,7);

    VectorDisplay vectorWindow;
    vectorWindow.setFC(*curve);
    vectorWindow.show();

    delete curve;

    return app.exec();
}//*/

#include <QApplication>
#include "display.h"
#include "VectorDisplay.h"
 using namespace std;

 int main(int argc, char *argv[]) {
     QApplication app(argc, argv);
     int width = 100, height = 100;

     Pixel **data = new Pixel*[height];
     for (int i = 0; i < height; ++i) {
         data[i] = new Pixel[width]{};
     }

     ImageWidget widget(data, width, height);
     widget.show();

     QObject::connect(&widget, &ImageWidget::shapeReady, [&](shape* figure) {
         VectorDisplay* vectorWindow = new VectorDisplay();
         vectorWindow->setFC(figure->FC);
         vectorWindow->show();
     });

     int result = app.exec();

     // Clean up
     for (int i = 0; i < height; ++i) delete[] data[i];
     delete[] data;

     return result;
 }// */
