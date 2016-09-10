#include <iostream>
using namespace std;

class Complex {
public:
 　　Complex();
　　 Complex(double);
 　　Complex(double,double);
 　　void write() const;
 
 　　Complex operator +(const Complex &) const;
　　 Complex operator -(const Complex &) const;
　　 Complex operator *(const Complex &) const;
　　 Complex operator /(const Complex &) const;
private:
 　　double real;
 　　double imag;
};

Complex::Complex(){
 　　real = imag = 0.0;
}
Complex::Complex(double re) {
 　　real = re;
 　　imag = 0.0;
};
Complex::Complex(double re,double im) {
 　　real = re;
 　　imag = im;
}

void Complex::write() const {
 　　cout << real << " + " << imag << 'i';
};

Complex Complex::operator + (const Complex &u) const {
 　　Complex v(real+u.real,imag+u.imag);
 　　return v;
}

Complex Complex::operator - (const Complex &u) const {
 　　Complex v(real-u.real,imag-u.imag);
 　　return v;
}

Complex Complex::operator* (const Complex &u) const {
 　　Complex v(real * u.real - imag * u.imag,real * u.imag + imag * u.real);
 　　return v;
}

Complex Complex::operator / (const Complex &u) const {
 　　double temp = u.real * u.real + u.imag * u.imag;
 　　Complex v( (real * u.real + imag * u.imag ) / temp, ( imag * u.real - real * u.imag ) / temp);
 　　return v;
}



