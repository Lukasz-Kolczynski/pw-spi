#include <iostream>
#include <string>
#include <cstdlib>


class Item
{
    public:
    const std::string& getName()  {
        return name;
    }
    unsigned int getID() {return id;}
    static unsigned int getCount() {
        return count;
        }

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

    virtual float getDamage() override {
        return baseDamage * sharpness; 
        }
    virtual bool isBroken() override {
        return sharpness <= 0.0f;
        }
    virtual void use() override {
        print();
        if (!isBroken()) sharpness-=0.1f;
    }
    virtual void repair() override {
        if (sharpness <1.0f) sharpness = std::min(sharpness * 1.1f , 1.0f);
    }

private:
    const float baseDamage = 8.125;
    float sharpness = 0.5;

};

class Hammer : public Weapon{
public:
    Hammer() : Weapon("Hammer") {};
    ~Hammer() {std::cout << "Hammer object is being destroyed..." << std::endl;};
    virtual float getDamage() override {
        if (durability > 0) {
            return damage;
        }
        else {
            return 0.0f;
        }
    }
    virtual bool isBroken() override {
        return durability <= 1.0f;
    }
    virtual void use() override {
        print();
        if (!isBroken()) durability -= 1;
    }
    virtual void repair() override {
        durability = defaultDurability;
    }


private:
    const unsigned int defaultDurability = 4;
    const float damage = 3.5;
    unsigned int durability = defaultDurability;
};

int main () {
    Weapon *equipment[4] = {
        new Sword,
        new Hammer,
        new Sword,
        new Hammer
    };

}