#include <QApplication>
#include "display.h"
#include "VectorDisplay.h"
#include "fstream"

 using namespace std;

struct VectorDisplayList{
    VectorDisplay* window = nullptr;
    VectorDisplayList* next = nullptr;
    VectorDisplayList(VectorDisplay* win, VectorDisplayList* n=nullptr): window(win) ,next(n){};
    ~VectorDisplayList(){if(next)delete next;window = nullptr; next = nullptr;}
};

 int main(int argc, char *argv[]) {
     VectorDisplayList* windows =nullptr;
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
        windows = new VectorDisplayList(vectorWindow, windows);
        ofstream OutFile("FC.txt",ios::trunc);
        for(int i = 0; i < figure->N;i++){
            OutFile<<figure->FC.C[i]<<endl;
        }
        OutFile.close();
     });

     int result = app.exec();

     // Clean up
     for (int i = 0; i < height; ++i) delete[] data[i];
     delete[] data;
     delete windows;

     return result;
 }// */
