#ifndef PATH_H
#define PATH_H
#include "Complex.h"

struct RotatorCoeficients{
    int N=9;
    Complex* CW; //clockwise
    Complex* CCW;//counter clockwise
    Complex* NR; //no rotation
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
    void reSampling();// will interpolate between the Paths and add evenly spaced points for better Fourier transform
    void add(int x, int y);
    void RDP(Path* S, Path* E);
    /*Rotator* FourierSetP;
    Rotator* offset;
    Rotator* FourierSetN;*/
};





#endif // PATH_H
