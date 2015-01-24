#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <vector>

class Item
{
    public:
        Item(std::string g_name = "Unknown Name", std::string g_type = "Unknown Type", int g_damage = 0);
        std::string getName();
        int getDamage();
    private:
        std::string name;
        std::string type;
        int damage;
};

class Inventory
{
    public:
        Inventory();
        bool isEmpty();
        void addItem(Item item);
        std::vector<Item> getItems();
        Item getItemByName(std::string name);
        Item getItemById(int id);

    private:
        std::vector<Item> items;
};

#endif // INVENTORY_H
