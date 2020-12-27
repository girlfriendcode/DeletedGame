//
// Created by valeria on 28.11.2020.
//
#include "../include/ItemCollector.h"

ItemCollector::ItemCollector(Level &level, std::string &name, std::string &fileName, float x, float y,
                             float w, float h, myView &view, std::map<std::string, std::string> properties) : Unit(
        level, name, fileName, x, y, w, h, view, properties) {
}

void ItemCollector::takeItem(Item *item) {
    inventory.push_back(item);
    item->state = Item::STATE::onInvent;
    basicStats["time"] -= 5;
}
//мб стоит добавить хоть какой-то максимальный размер вектора? хотя, предметов на поле не дофига

void ItemCollector::throwItem(Item *item) {

    if (inventory.empty()) {
        std::cout << "There is nothing to delete!" << std::endl;
        return;
    }
    int i = 0;
    while (inventory[i] != item) {
        i++;
        if (i > inventory.getSize()) {
            std::cout << "Item wasn't found!" << std::endl;
            return;
        }
    }
    item->state = Item::STATE::onMap;
    inventory.erase(i);
    //добавляем предмет на поле
}

void ItemCollector::throwItem(float x, float y) {
    if (inventory.empty()) {
        std::cout << "There is nothing to delete!" << std::endl;
        return;
    }
    float newX = x;
    float newY = y;
    for (int i = 0; i < inventory.getSize(); i++) {
        inventory[i]->x = newX;
        inventory[i]->y = newY;
        inventory[i]->w = w;
        inventory[i]->h = h;
        inventory[i]->state = Item::STATE::onMap;
        inventory.erase(i);
        newX += 30;
        newY += 30;
    }
    //добавляем на поле весь массив c обработкой состояния
}