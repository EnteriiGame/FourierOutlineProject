#include "Complex.h"
#include "Path.h"
#include <cmath>
#include <vector>
#include <iostream>


float threashold = .5f;

using namespace std;

RotatorCoeficients::RotatorCoeficients() {
    C = new Complex[1];
}


void RotatorCoeficients::setN(int n) {
    if (N != n) {
        delete[] C;
        N = n;
        C = new Complex[N];
    }
}

RotatorCoeficients::~RotatorCoeficients() {
    delete[] C;
    C = nullptr;
}

shape::shape(int x, int y) {
    start = new Path(x, y, N);
    end = start;
    N++;
    FC.setN(N);
}

shape::~shape() {
    Path* current = start;
    while (current) {
        Path* next = current->next;
        delete current;
        current = next;
    }
    start = nullptr;
}

Path::~Path() {
}


float pointDis(int px, int py, int x1, int y1, int x2, int y2) {
    if (x1 == x2 && y1 == y2) {
        return sqrt((px - x1) * (px - x1) + (py - y1) * (py - y1));
    }
    return abs((y2 - y1) * px - (x2 - x1) * py + x2 * y1 - y2 * x1) /
           sqrt((y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1));
}

void sortDistances(float* dis, Path** toAdd, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (dis[i] > dis[j]) {
                std::swap(dis[i], dis[j]);
                std::swap(toAdd[i], toAdd[j]);
            }
        }
    }
}

void shape::RDP(Path* S, Path* end) {
    if (!S || !end || S == end) return;

    Path* farthest = nullptr;
    float maxDist = 0;
    Path* current = S->next;

    while (current && current != end) {
        float dist = pointDis(current->x, current->y, S->x, S->y, end->x, end->y);
        if (dist > maxDist) {
            maxDist = dist;
            farthest = current;
        }
        current = current->next;
    }

    if (maxDist > threashold) {
        RDP(S, farthest);
        RDP(farthest, end);
    } else {
        vector<Path*> toDelete;
        current = S->next;
        while (current && current != end) {
            toDelete.push_back(current);
            current = current->next;
        }
        for (Path* p : toDelete) {
            delete p;
            //N--;
        }
        S->next = end;
        end->prev = S;
    }
}

void shape::SimplifyPath(){
    RDP(start,end);
};//RDP Rammer-Doglas-Peucker

void shape::add(int x, int y){
    Path* newPath = new Path(x, y, N);
    end->next = newPath;
    newPath->prev = end;
    end = newPath;
}

bool isPow2(int a){
    while (a>2){if(a%2==1) return false;
    a/=2;}
    return true;
}

void shape::Interpolation() {

    N = 0;
    Path* temp = start;
    while (temp) {
        N++;
        temp = temp->next;
    }
    int targetCount = 1;
    while (targetCount < N) {
        targetCount *= 2;
    }
    //cout<<"N="<<N<<endl;

    while (N < targetCount) {
        Path* maxGapStart = nullptr;
        float maxGapSize = 0;
        temp = start;
        while (temp->next) {
            float gap = sqrt(pow(temp->next->x - temp->x, 2) + pow(temp->next->y - temp->y, 2));
            if (gap > maxGapSize) {
                maxGapSize = gap;
                maxGapStart = temp;
            }
            temp = temp->next;
        }

        if (maxGapStart) {
            int newX = (maxGapStart->x + maxGapStart->next->x) / 2;
            int newY = (maxGapStart->y + maxGapStart->next->y) / 2;
            Path* newPoint = new Path(newX, newY, N);

            newPoint->next = maxGapStart->next;
            newPoint->prev = maxGapStart;
            maxGapStart->next->prev = newPoint;
            maxGapStart->next = newPoint;
            N++;
            //cout<<"New "<<N<<endl;
        }
    }
}


void bitReversal(Complex* data, int N) {
    int j = 0;
    for (int i = 1; i < N; i++) {
        int bit = N >> 1;
        while (j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;
        if (i < j) {
            Complex temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }
}

void shape::FFT(Complex* data, int N) {
    bitReversal(data, N);

    for (int len = 2; len <= N; len *= 2) {
        float angle = -2 * PI / len;
        Complex wLen = ComplexExp(angle);

        for (int i = 0; i < N; i += len) {
            Complex w = Complex(1, 0);
            for (int j = 0; j < len / 2; ++j) {
                Complex u = data[i + j];
                Complex v = w * data[i + j + len / 2];
                data[i + j] = u + v;
                data[i + j + len / 2] = u - v;
                w *= wLen;
            }
        }
    }
}

void shape::applyFFT() {

    Complex* Z = new Complex[N];
    Path* current = start;
    for (int i = 0; i < N; i++) {
        Z[i] = Complex(current->x, current->y);
        current = current->next;
    }

    FC.setN(N);
    FFT(Z, N);

    for (int k = 0; k < N; ++k) {
        FC.C[k] = Z[k];
    }
    delete[] Z;
}
