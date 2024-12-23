#include <iostream>
#include <string>

class Person
{
private:
    int age;
    std::string name;
    static int counter;

public:
    Person() :age(1), name("Unknown")        // domyślny konstruktor
    {
        std::cout << "Default constructor called" << std::endl;
        ++counter;
    }

    Person(const int _age, const std::string& _name) : age(_age), name(_name)  // konstruktor z parametrami
    {
        std::cout << "Params constructor called" << std::endl;
        ++counter;
    } 

void showInfo() 
{
    std::cout << "This person have name " << name << " and have " << age << " years.\n" << "How many people: "<< counter <<std::endl;  // metoda wypisująca dane
}


~Person () 
{
    std::cout <<"Destructor called for: " << name << std::endl;  // destruktor zwalniający pamięć
}

Person operator+(const Person &source) const  // przeciążony operator +(dodawania)
{
    return Person (age + source.age, name + source.name);
}

Person& operator=(const Person &source) // przeciążony operator =(przypisania)
{
    if(this != &source)
    {
        age = source.age;
        name = source.name;
    }
    return *this;
}

};

int Person::counter = 0;

int main()
{
    Person p1; // domyślny konstruktor
    p1.showInfo();  // metoda wypisująca dane

    Person p2(18, "Lucjan");  // konstruktor z parametrami
    p2.showInfo();  // metoda wypisująca dane

    Person p3 = p1 + p2; // przeciążony operator +(dodawania)
    p3.showInfo();

    p3 = p1;  // przeciążony operator =(przypisania)
    p3.showInfo();

    return 0;
}