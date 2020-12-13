//
// Created by mi on 23.11.2020.
//


#include <SFML/Graphics/RenderWindow.hpp>
#include "../include/FieldObject.h"

using namespace sf;

FieldObject::FieldObject(Level &level, std::string &name, std::string &fileName, float x, float y, float w, float h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->level = level;
    this->name = name;
    this->image.loadFromFile("../res/img/" + fileName);
    this->texture.loadFromImage(image);
    this->sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, 0, w, h));
    if (!font.loadFromFile("../res/fonts/GameFont.ttf")) {
        std::cout << "Font can't be loaded!" << std::endl;
    }
}

void FieldObject::update(float time) {
    sprite.setPosition(x, y);//передаем координаты появления спрайта
}

void FieldObject::draw(RenderWindow &window) {
    window.draw(sprite);
}

