//
// Created by valeria on 14.12.2020.
//

#include "../include/Bullet.h"

Bullet::Bullet(Level &level, float x, float y, float temX, float temY) {
    this->x = x;
    this->y = y;
    this->tempX = temX;
    this->tempY = temY;
    this->w = 16;
    this->h = 16;
    this->isAlive = true;
    this->level = level;
    this->objectsStatic = level.getAllStaticObjects();
    this->units = level.getAllDynamicObjects();
    this->name = "bullet";
    this->fileName = "bullet.png";
    this->image.loadFromFile("../res/img/" + fileName);
    this->image.createMaskFromColor(Color(0, 0, 0));
    this->texture.loadFromImage(image);
    this->sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, 0, w, h));
}

void Bullet::toPoint(Vector2f pos) {
    tempX = pos.x;
    tempY = pos.y;
}

void Bullet::doShoot(float time) {
    float distance = 0;
    distance = sqrt((tempX - x) * (tempX - x) + (tempY - y) * (tempY -
                                                               y));//считаем дистанцию (расстояние от точки А до точки Б). используя формулу длины вектора
    float tga = tan((tempY - y) / (tempX - x));
    if (distance > 2) {
        x += 0.3 * time * (tempX - x) / distance;//идем по иксу с помощью вектора нормали
        y += 0.3 * time * (tempY - y) / distance;//идем по игреку так же
    }
}

void Bullet::update(float time) {
    if (x <= 0)
        x = 1;// задержка пули в левой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки
    if (y <= 0) y = 1;
    for (int i = 0; i < units.size(); i++) {//проход по объектам solid
        if (getRect().intersects(units[i].rect)) //если этот объект столкнулся с пулей,
        {
            units[i].sprite.setColor(Color::Red);
            isAlive = false;// то пуля умирает
        }


    }
    for (auto it = level.getAllStaticObjects().begin(); it != level.getAllStaticObjects().end(); it++) {
        if (getRect().intersects(it->rect)) {
            isAlive = false;
            if (it->name == "glass" || it->name == "part") {
                level.getAllStaticObjects().erase(it);
            }
        }

    }

    sprite.setPosition(x, y);//задается позицию пуле
}

void Bullet::draw(RenderWindow &window) {
    window.draw(sprite);
}

