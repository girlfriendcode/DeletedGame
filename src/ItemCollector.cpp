//
// Created by valeria on 28.11.2020.
//
#include "../include/ItemCollector.h"

ItemCollector::ItemCollector(Level &level, std::string &name, std::string &fileName, float x, float y,
                             float w, float h, myView &view) : Unit(level, name, fileName, x, y, w, h, view) {
}

void ItemCollector::takeItem(Item *item) {
    inventory.push_back(item);
    item->state = Item::STATE::onInvent;
    basicStats["time"] -= 5;
}
//мб стоит добавить хоть какой-то максимальный размер вектора? хотя, предметов на поле не дофига

void ItemCollector::throwItem(Item *item) {
    auto iter = inventory.begin();
    if (inventory.empty()) {
        std::cout << "There is nothing to delete!" << std::endl;
        return;
    }
    while (*iter != item) {
        iter++;
        if (iter == inventory.end()) {
            std::cout << "Item wasn't found!" << std::endl;
            return;
        }
    }
    item->state = Item::STATE::onMap;
    inventory.erase(iter);
    //добавляем предмет на поле
}

void ItemCollector::throwItem() {
    if (inventory.empty()) {
        std::cout << "There is nothing to delete!" << std::endl;
        return;
    }
    inventory.clear();
    //добавляем на поле весь массив c обработкой состояния
}