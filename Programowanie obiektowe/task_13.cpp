#include <iostream>
#include <vector>
#include <string>

class Vector 
{
private:


public:
    virtual double length() const = 0;
    virtual void normalize() = 0;
    virtual ~Vector() = default;

};


class Vector2D : Vector 
{


};


class Vector3D : Vector2D
{


};

int main()
{


    return 0;
}