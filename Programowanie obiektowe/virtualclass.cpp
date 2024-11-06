#include <iostream>
#include <string>

class Car {
public:
    void drive() {std::cout << " brum brum\n"; };
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

class ElectricCar :  public Car {
public:
    int getBatteryCapacity();
};

class HybridCar : public PetrolCar, public ElectricCar {

};