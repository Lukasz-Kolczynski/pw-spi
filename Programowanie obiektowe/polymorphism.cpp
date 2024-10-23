// kosmatka.pl/pw/po/po4.pdf

#include<iostream>

class Bazowa {
public:
    virtual void wirtualna(){
        std::cout << "Metoda wirtualna w klasie bazowej" << std::endl;

    }
    void normalna(){
        std::cout << " Metoda normalna w klasie bazowej" << std::endl;

        }
};

class Pochodna : public Bazowa {
public:
virtual void wirtualna(){
    std::cout << "Metoda wirtualna w klasie bazowej" << std::endl;

    }
    void normalna(){
        std::cout << " Metoda normalna w klasie bazowej" << std::endl;

    }
};
int main(){
    Bazowa b;
    Pochodna p;
    p.normalna();
    return 0;
}
