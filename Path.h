#ifndef PATH_H
#define PATH_H
#include "Complex.h"

struct RotatorCoeficients {
    void setN(int n = 1);
    int N;
    Complex* C;
    RotatorCoeficients();
    ~RotatorCoeficients();
};

struct Path{
    int x, y, n;
    Path * next;
    Path * prev;
    Path(int px, int py,int I=0, Path* P=nullptr, Path* N=nullptr) : x(px), y(py),n(I), next(N), prev(P) {};
    ~Path();
    void remove();
};

float pointDis(int px, int py,int x1,int y1,int x2,int y2);

struct shape{
    Path* start;
    Path* end;
    int N = 0;
    shape(int x, int y);
    ~shape();
    void SimplifyPath();//RDP Rammer-Doglas-Peucker
    void add(int x, int y);
    void RDP(Path* S, Path* E);
    RotatorCoeficients FC;//

    void Interpolation();//i need for the ammount of points to be a power of 2 so i will interpolate between the longest streches untill it is
    void FFT(Complex* data, int N);
    void applyFFT();


};





#endif // PATH_H
