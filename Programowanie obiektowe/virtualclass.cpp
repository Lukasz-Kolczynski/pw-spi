#include <iostream>
#include <string>

class Car {
public:
    void drive() {std::cout << "Drive " << vin << std::endl; };
    void setVin(const std::string &_vin) { this ->vin = _vin; }
private:
    std::string manufacturer;
    std::string model;
    std::string vin;
};

class PetrolCar : public Car {
public:
    int getFuelCapacity();


};

class ElectricCar :  virtual public Car {
public:
    int getBatteryCapacity();
};

class HybridCar : public PetrolCar, public ElectricCar {

};

int main() {
    HybridCar hc;
    
    /* 
    PetrolCar &pc = static_cast<PetrolCar&>(hc);
    ElectricCar &ec = static_cast<ElectricCar&>(hc);
    */

    pc.setVin("40285278352543");
    ec.setVin("45345423");

    pc.drive();
    ec.drive();

    return 0;
}