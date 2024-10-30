#include <iostream>
#include <string>



class Item
{
    public:
    const std::string& getName()  {
        return name;
    }
    unsigned int getID() {return id;}
    static unsigned int getCount() {return count;}

protected:
    Item(const std::string &name) : name(name), id(++count) {} ;

private:
    std::string name;
    unsigned int id;
    static unsigned int count;

};

unsigned int Item::count = 0;



class Weapon : public Item
{
public:
    Weapon(const std::string &name) : Item(name) {};
    virtual ~Weapon() {}
    virtual float getDamage() = 0;
    virtual bool isBroken() = 0;
    virtual void use() = 0;
    virtual void repair() = 0;

    void print() {
        if (isBroken()) {
            std::cout <<"Weapon " << getName() << " (" << getID() << ") cannot be used, as its broken." << std::endl;
        }
        else {
            std::cout <<"Weapon " << getName() << " (" << getID() << ") results in " << getDamage() << "of damage points." << std::endl;
        }


    }
};

class Sword : public Weapon{
public:
    Sword() : Weapon ("Sword") {}
    ~Sword() { std::cout << "Sword object is being destroyed..." << std::endl; }

    float getDamage() override {return baseDamage * sharpness; }
    bool isBroken() override {return <= 0.0f;}
    void use() override {
        print();
        if (!isBroken)
    }

private:
    const float baseDamage = 8.125;
    float sharpness = 0.5;

};