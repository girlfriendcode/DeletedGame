//
// Created by valeria on 14.12.2020.
//

#ifndef DELETEDGAME_BULLET_H
#define DELETEDGAME_BULLET_H

#include "FieldObject.h"
#include <cmath>
/**
 * Класс пули
 */
class Bullet {
public:
    Bullet(Level &level, float x, float y, float temX, float temY);

    std::vector<MapObject> objectsStatic;//объекты карты
    std::vector<MapObject> units;
    Level level;
    Texture texture;
    Sprite sprite;
    Image image;
    std::string name;
    std::string fileName;
    float tempX;
    float tempY;
    float x;
    float y;
    float w;
    float h;
    bool isAlive;

    void toPoint(Vector2f pos);

    void doShoot(float time);

    void update(float time);

    void draw(RenderWindow &window);

    FloatRect getRect() const { return {x, y, h, w}; };

};

#endif //DELETEDGAME_BULLET_H
