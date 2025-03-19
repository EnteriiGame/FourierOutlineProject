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
}
