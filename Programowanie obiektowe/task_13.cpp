#include <iostream>
#include <cmath>
#include <stdexcept>
#include <math.h>

template <typename T>
class Vector 
{
private:

public:
    virtual double length() const = 0;
    virtual void normalize() = 0;
    virtual ~Vector() = default;

};

template <typename T>
class Vector2D : public Vector<T>
{
private:
T a;
T b;

public:
Vector2D(T _a, T _b) : a(_a), b(_b) 
{

}

virtual double length() override
{
    double a_pow = pow(a,2);
    double b_pow = pow(b,2);
    double result = sqrt(a_pow + b_pow);
    return result;
}

virtual void normalize() override
{
    double length_of_vec = length();
    double a_vec = a / length_of_vec;
    double b_vec = b / length_of_vec;
    a = a_vec;
    b = b_vec;
}

friend std::ostream& operator <<(std::ostream& out, const Vector2D<T> & vec) {
    out << "Pierwsza składowa: " << vec._a << "Druga składowa: " << vec._b << std::endl;
    return out;
}
};

template <typename T>
class Vector3D : Vector2D<T>
{
private:
T c;

public:
Vector3D(T _a, T _b, T _c) : Vector2D<T>(_a, _b), c(_c) 
{

}

friend std::ostream& operator <<(std::ostream& out, const Vector3D<T> & vec){
     out << "Pierwsza składowa: " << vec._a << "Druga składowa: " << vec._b << "Trzecia składowa: " << vec._c << std::endl;
     return out;
}
};

int main()
{


    return 0;
}