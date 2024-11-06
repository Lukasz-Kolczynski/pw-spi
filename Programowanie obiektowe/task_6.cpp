#include <iostream>

class Animal {
public:
    virtual void Sound() const = 0;
    virtual ~Animal() {}

};

class Dog : public Animal {
private:
    const char* name;
    int age;
    static int dogs_value;

public:
    Dog(const char* name, int age)
    {
        this-> name = name;
        this-> age = age;
        dogs_value++;
    }

~Dog() override {
    delete [] name;
    dogs_value--;
}

void Sound() const override
{
    std::cout <<"Woof! I am: " << name << std::endl;
}

Dog(const Dog& other)
{
    name = other.name;
    age = other.age;
    dogs_value++;
}

Dog& add(const Dog& other)
{
    if (this != &other)
    {
        delete [] name;
        name = other.name;
        age = other.age;
    }
    return *this;
}

const char* getName() const
{
    return name;
}

};











int main(){




    return 0;
}