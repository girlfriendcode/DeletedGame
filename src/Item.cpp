//
// Created by valeria on 30.11.2020.
//

#include "../include/Item.h"

Item::Item(Level &level, int weight, std::string &name, std::string &fileName, float x, float y, float w, float h)
        : FieldObject(level, name, fileName, x, y, w, h) {
    this->weight = weight;
    this->state = Item::STATE::onMap;
}

void Item::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}
