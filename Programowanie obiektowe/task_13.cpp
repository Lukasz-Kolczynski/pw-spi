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
protected:
T a;
T b;

public:
Vector2D(T _a, T _b) : a(_a), b(_b) 
{

}

double length() const override
{
    double a_pow = pow(a,2);
    double b_pow = pow(b,2);
    double result = sqrt(a_pow + b_pow);
    return result;
}

void normalize() override
{
    double length_of_vec = length();
    double a_vec = a / length_of_vec;
    double b_vec = b / length_of_vec;
    a = a_vec;
    b = b_vec;
}

friend std::ostream& operator <<(std::ostream& out, const Vector2D<T> & vec) {
    out << "Pierwsza składowa: " << vec.a << "Druga składowa: " << vec.b << std::endl;
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
     out << "Pierwsza składowa: " << vec.a << "Druga składowa: " << vec.b << "Trzecia składowa: " << vec.c << std::endl;
     return out;
}

double length() const override
{
    double a3_pow = pow(this->a,2);
    double b3_pow = pow(this->b,2);
    double c3_pow = pow(c,2);

    double result3 = sqrt(a3_pow + b3_pow + c3_pow);
    return result3;
}

void normalize() override
{
    double length3_of_vec = length();
    double a3_vec = this->a / length3_of_vec;
    double b3_vec = this->b / length3_of_vec;
    double c3_vec = c / length3_of_vec;
    c = c3_vec;
    this->a = a3_vec;
    this->b = b3_vec;
}


};

int main()
{
    Vector2D<double> vec2D(3.7, 4.2);
    std::cout << "wektor 2D przed normalizacją: " << vec2D << std::endl;
    std::cout << "Długość przed normalizacji: " << vec2D.length() << std::endl;

    vec2D.normalize();
    std::cout << "wektor 2D po normalizacji: " << vec2D << std::endl;
    std::cout << "Długość po normalizacji: " << vec2D.length() << std::endl;


    Vector3D<int> vec3D(3 ,2, 5);
    std::cout << "wektor 3D przed normalizacją: " << vec3D << std::endl;
    std::cout << "Długość przed normalizacji: " << vec3D.length() << std::endl;

    vec3D.normalize();
    std::cout << "wektor 3D po normalizacji: " << vec3D << std::endl;
    std::cout << "Długość po normalizacji: " << vec3D.length() << std::endl;

    return 0;
}