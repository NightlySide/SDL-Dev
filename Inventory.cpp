#include "Inventory.h"

Inventory::Inventory()
{
    //ctor
}

bool Inventory::isEmpty()
{
    return sizeof(items)==0;
}

void Inventory::addItem(Item item)
{
    items.push_back(item);
}

std::vector<Item> Inventory::getItems()
{
    return items;
}

Item Inventory::getItemByName(std::string item_name)
{
    Item item;
    for(int unsigned i = 0; i<(sizeof(items)/sizeof(Item)); i++)
    {
        if (items[i].getName() == item_name)
        {
            item = items.at(i);
        }
    }
    return item;
}

Item Inventory::getItemById(int item_id)
{
    return items.at(item_id);
}

Item::Item(std::string g_name, std::string g_type, int g_damage)
{
    name = g_name;
    type = g_type;
    damage = g_damage;
}

std::string Item::getName()
{
    return name;
}

int Item::getDamage()
{
    return damage;
}
