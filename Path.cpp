#include "Complex.h"
#include "Path.h"
#include <cmath>

float threashold = .5f;

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

Path::~Path() {}

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
                float tmpDis = dis[i]; dis[i] = dis[j]; dis[j] = tmpDis;
                Path* tmpPath = toAdd[i]; toAdd[i] = toAdd[j]; toAdd[j] = tmpPath;
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
        current = S->next;
        while (current && current != end) {
            Path* next = current->next;
            delete current;
            current = next;
        }
        S->next = end;
        end->prev = S;
    }
}

void shape::SimplifyPath() {
    RDP(start, end);
}

void shape::add(int x, int y) {
    Path* newPath = new Path(x, y, N);
    end->next = newPath;
    newPath->prev = end;
    end = newPath;
}

void shape::Interpolation() {
    N = 0;
    for (Path* temp = start; temp; temp = temp->next) { N++; }
    int k = 1;
    while (k < N) k *= 2;
    k -= N;
    if (k == 0) return;

    Path* temp = start;
    if (!temp) return;

    Path** gaps = new Path*[k];
    int* dis = new int[k];
    int* cuts = new int[k];

    for (int i = 0; (i < k) && temp->next; temp = temp->next, i++) {
        gaps[i] = temp;
        dis[i] = pow(2, (temp->x - temp->next->x)) + pow(2, (temp->y - temp->next->y));
        cuts[i] = 1;
    }

    for (int i = 0; i < k - 1; i++) {
        int maxDis = i;
        for (int j = i + 1; j < k; j++) {
            if (dis[j] < dis[maxDis]) {
                maxDis = j;
            }
        }
        int tempDis = dis[i]; dis[i] = dis[maxDis]; dis[maxDis] = tempDis;
        Path* tempGap = gaps[i]; gaps[i] = gaps[maxDis]; gaps[maxDis] = tempGap;
        int tempCuts = cuts[i]; cuts[i] = cuts[maxDis]; cuts[maxDis] = tempCuts;
    }

    int minD = dis[0];
    for (; temp->next; temp = temp->next) {
        int d = pow(2, (temp->x - temp->next->x)) + pow(2, (temp->y - temp->next->y));
        if (d > minD) {
            for (int i = 0; i < k; i++) {
                if (d < dis[i]) break;
                for (int j = 1; j < i + 1; j++) {
                    dis[j - 1] = dis[j];
                    gaps[j - 1] = gaps[j];
                }
            }
            minD = dis[0];
        }
    }

    int i = k - 1; int j = 0;
    while (i != j) {
        if (dis[i] / float(cuts[i] + 1) >= dis[j]) {
            cuts[i]++; cuts[j]--; j++;
        } else i--;
    }

    for (int i = 0; i < k; i++) {
        temp = gaps[i];
        int x1 = temp->x;
        int y1 = temp->y;
        int x2 = temp->next->x;
        int y2 = temp->next->y;
        for (int j = 0; j < cuts[i]; j++) {
            temp->next = new Path(x1 + (((x2 - x1) * (j + 1)) / float(cuts[i])),
                                  y1 + (((y2 - y1) * (j + 1)) / float(cuts[i])), 0,
                                  temp, temp->next);
            temp = temp->next;
        }
    }

    N = 0;
    for (Path* temp = start; temp; temp = temp->next) { N++; }

    delete[] gaps;
    delete[] dis;
    delete[] cuts;
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
