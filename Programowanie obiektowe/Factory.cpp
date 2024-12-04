#include <iostream>
#include <vector>

class Item {
public:
    virtual void show() = 0;
};

class ItemSword : public Item {
public:
    virtual void show() override {
        std::cout << "This is Sword" << std::endl;
    }
};

class ItemHammer : public Item {
public:
    virtual void show() override {
        std::cout << "This is Hammer" << std::endl;
    }
};

class ItemFactory {
public: 
    enum ItemType {Sword, Hammer};
    static Item* createItem(ItemType type) {
        switch(type)
        {
            case Sword: return new ItemSword();
            case Hammer: return new ItemHammer();
            default: return nullptr;
        }
    }
private:
    ItemFactory() = default;
};

int main()
{
    srand(time(NULL));

    std::vector<Item*> items;
    for (int i = 0; i < 10; i++)
    {
        ItemFactory::ItemType type = (rand() % 2) ? ItemFactory::ItemType::Sword : ItemFactory::ItemType::Hammer;
        items.push_back(ItemFactory::createItem(type));
    }

    for (int i = 0; i < items.size(); i++)
    {
        items[i]->show();
    }

    return 0;
}