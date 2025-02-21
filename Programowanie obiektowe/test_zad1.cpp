/*
===================


zad 1


===================
*/




#include <iostream>
#include <vector>
#include <stdexcept>


template <typename T>
class Shape {
public:
    virtual T area() const = 0;
    virtual ~Shape() = default;
};

template <typename T>
class Rectangle : public Shape<T> {
private:
    T width, height;
public:
    Rectangle(T w, T h) : width(w), height(h) {
        if (width <= 0 || height <= 0) {
            throw std::invalid_argument("Podane wymiary nie spełniają warunków.(Params>0)");
        }
    }    T area() const override {
        return width * height;
    }
};
template <typename T>
class Square : public Rectangle<T> {

public:
    Square(T s) : Rectangle<T>(s, s) {
        if (s <= 0) {
            throw std::invalid_argument("Podane wymiary nie spełniają warunków.(Side>0)");
        }
    }
};


int main() {
    try {
        Rectangle<int> rectINT(10, 7);
        Square<int> squareINT(2);
        std::cout << "Pole prostokąta dla int: " << rectINT.area() << std::endl;
        std::cout << "Pole kwadratu dla int: " << squareINT.area() << std::endl; 


        Rectangle<double> rectDOUBLE(7.7, 4.8);
        Square<double> squareDOUBLE(4.7);
        std::cout << "Pole prostokąta dla double: " << rectDOUBLE.area() << std::endl;
        std::cout << "Pole kwadratu dla double: " << squareDOUBLE.area() << std::endl; 
        Square<int> invalidSquare(1);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }    
    
    return 0;
}
