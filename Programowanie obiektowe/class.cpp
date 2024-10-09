class Complex {
    public:
        Complex(double _re, double _im);
        Complex(double _re);
        double real() const;
        double imag() const;
        Complex operator+(const Complex &c); // Complex + Complex
        Complex operator-(const Complex &c); // Complex - Complex
        Complex& operator+=(const Complex &c); // Complex += Complex
        Complex& operator-=(const Complex &c); // Complex -= Complex
        Complex operator*(double x); // Complex * double
        Complex operator-(); // operator unarny (jednoargumentowy)


    a + b
    a - b 
    a += b 
    a -= b 
    -a
    a (Complex) * b (double)
    std::ostream <<

    private:
        double re;
        double im;

};

std::ostream& operator<<(std::ostream &os, const Complex &obj);