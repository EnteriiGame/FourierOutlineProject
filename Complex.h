#ifndef COMPLEX_H
#define COMPLEX_H
const int N = 10;
const double PI = 3.1415926535897;
//float sin(float x);
//float cos(float x);


#include <cmath>

struct Complex{
    float rel=0;
    float img=0;
    Complex(float a, float b):rel(a) , img(b){};

    Complex Conjugate();
    Complex operator+(Complex other);
    Complex operator-(Complex other);
    Complex operator*(Complex other);
    Complex operator*(float other);
    Complex operator/(Complex other);
    Complex operator/(float other);

};
Complex ComplexExp(double theata);



#endif // COMPLEX_H
