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
