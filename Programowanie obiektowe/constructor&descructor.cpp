#include <iostream>

class Bazowa
{
    public:
    Bazowa() {
        std::cout << "Konstruktor klasy bazowej" << std::endl;
    }
    ~Bazowa(){
        std::cout << "Destruktor klasy bazowej" << std::endl;

    }
};

class Pochodna : Bazowa
{
    public:
        Pochodna() {
            std::cout << "Konstruktor klasy pochodnej" << std::endl;

        }
        ~Pochodna(){
            std::cout << "Destruktor klasy pochodnej" << std::endl;

        }
};

int main()
{
    Pochodna p;
    return 0;

}