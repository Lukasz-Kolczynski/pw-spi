#include <iostream>
#include <cmath>
#include <stdexcept>


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

friend std::ostream& operator <<( const std::ostream& out, const Vector2D & vec);
    os << "Pierwsza składowa: " << vec.a << "Druga składowa: " << vec.b << std::endl;
    return os;
};

template <typename T>
class Vector3D : Vector2D<T>
{
private:
T c;

public:
Vector3D(T _c) : c(_c) 
{

}

friend std::ostream& operator <<( const std::ostream& out, const Vector3D & vec);
     os << "Pierwsza składowa: " << vec.a << "Druga składowa: " << vec.b << "Trzecia składowa: " << vec.c << std::endl;
     return os;
    
};

int main()
{


    return 0;
}