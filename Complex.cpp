#include "Complex.h"

auto sq= [](float x)->float{return (x*x);};
float sin(float x){
    double f=1;
    double x2 = x * x;
    for (int n = N - 1; n > 0; --n) {
        f = 1 - (x2 / ((2 * n) * (2 * n + 1))) * f;
    }
    return x * f;}

float cos(float x){
    double f=1;
    double x2 = x * x;
    for (int n = N - 1; n > 0; --n) {
        f = 1 - (x2 / ((2 * n-1) * (2 * n))) * f;}
    return x * f;}
    Complex Complex::Conjugate(){
        return Complex(rel,-img);
    }
    Complex Complex::operator+(Complex other){
        return Complex(rel+other.rel,img+other.img);
    };
    void Complex::operator+=(Complex other){
        rel+=other.rel;
        img+=other.img;
    };
    Complex Complex::operator-(Complex other){
        return Complex(rel-other.rel,img-other.img);
    };
    Complex Complex::operator*(Complex other){
        return Complex(rel*other.rel - img*other.img,rel*other.img + img*other.rel);
    };
    void Complex::operator*=(Complex other){
        float a=rel;
        rel = rel*other.rel - img*other.img;
        img =a*other.img + img*other.rel;
    };
    Complex Complex::operator*(float other){
        return Complex(rel*other,img*other);
    };
    Complex Complex::operator/(float other){
        return Complex(rel/other,img/other);
    };
    Complex Complex::operator/(Complex other){
        return Complex(((*this)*other.Conjugate())/(sq(other.rel)-sq(other.img)));
    };



    Complex ComplexExp(double theata){
        return(Complex(cos(theata),sin(theata)));
    };
