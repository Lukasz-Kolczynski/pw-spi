#include <iostream>
#include <string>

class Person
{
private:
    int age;
    std::string name;

public:
    Person() :age(0), name("Unknown")        // domyślny konstruktor
    {
        std::cout << "Default constructor called" << std::endl;
    }

    Person(const int _age, const std::string& _name) : age(_age), name(_name)  // konstruktor z parametrami
    {
        std::cout << "Params constructor called" << std::endl;
    } 

void showInfo() 
{
    std::cout << "This person have name " << name << " and have " << age << " years." <<std::endl;  // metoda wypisująca dane
}

};



int main()
{
    Person p1; // domyślny konstruktor
    p1.showInfo();  // metoda wypisująca dane

    Person p2(18, "Lucjan");  // konstruktor z parametrami
    p2.showInfo();  // metoda wypisująca dane

    return 0;
}