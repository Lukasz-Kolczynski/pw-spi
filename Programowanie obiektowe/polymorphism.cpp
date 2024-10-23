// kosmatka.pl/pw/po/po4.pdf

/*
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
*/



#include <iostream>
#include <string>


class Computer {
private:
    std::string manufacturer;
    std::string model;
    std::string cpu;
    unsigned int ramMemory;
    unsigned int diskMemory;

public:
    Computer(const std::string manufacturer, const std::string model, const std::string cpu, unsigned int ramMemory, unsigned int diskMemory)
    : manufacturer(manufacturer), model(model), cpu(cpu), ramMemory(ramMemory), diskMemory(diskMemory)
    {}

    void print() const {
        std::cout << manufacturer << " " << model << " " << cpu << " " << " " << ramMemory << " " << diskMemory << " " << std::endl;
    
    }

    void setManufacturer(std::string manufacturer)
    {
        this -> manufacturer = manufacturer;
    }

    void setModel(std::string model)
    {
        this -> model = model;
    }

    void setCpu(std::string cpu)
    {
        this -> cpu = cpu;
    }

    void setRamMemory(unsigned int ramMemory)
    {
        this -> ramMemory = ramMemory;
    }

    void setDiskMemory(unsigned int diskMemory)
    {
        this -> diskMemory = diskMemory;
    }



};

class Laptop : public Computer {
    private:
        unsigned int screen;
        unsigned int battery;

    public:

        Laptop(Computer&addLaptop, unsigned int screen, unsigned int battery)
        : Computer(addLaptop), screen(screen), battery(battery) {}

        void print() const {
            Computer::print();
            std::cout << battery << " Wh," << screen << "\" " << std::endl;

        }



};


class Desktop : public Computer {
    private:
    std::string formFactor;
    std::string psu;

    public:
        Desktop(const std::string manufacturer, const std::string model, const std::string cpu, unsigned int ramMemory, unsigned int diskMemory, std::string formFactor, std::string psu)
        : Computer(manufacturer, model, cpu, ramMemory, diskMemory),formFactor(formFactor), psu(psu)
        {}


};



int main() {
    Computer c("SNSV", "Longitude 555", "ill-1234X", 16, 512);
    std::cout << "Specyfikacja komputera:" << std::endl;
    c.print();
    std::cout << "Specyfikacja laptopa:" << std::endl;
    Laptop l(c, 15, 50);
    l.print();
    Desktop d("Optimus", "PW-000", "i13-4321X", 96, 4096, "SFF", "550W 80 Plus Gold");
    std::cout << "Specyfikacja desktopa:" << std::endl;
    d.print();
    return 0;
}