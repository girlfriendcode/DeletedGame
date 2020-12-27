//
// Created by valeria on 14.12.2020.
//

#ifndef DELETEDGAME_BULLET_H
#define DELETEDGAME_BULLET_H

#include "FieldObject.h"
#include "Shooter.h"
#include "Unit.h"
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
    /**
     * Координата по Х для цели пули
     */
    float tempX;
    /**
     * Координата по Y для цели пули
     */
    float tempY;

    float x;
    float y;
    float w;
    float h;
    bool isAlive;

    /**
     * Указываем направление стрельбы
     * @param pos
     */
    void toPoint(Vector2f pos);

    /**
     * Перемещение пули
     * @param time
     */
    void doShoot(float time);

    /**
     * Обновление состояния пули
     * @param time
     */
    void update(float time);

    void draw(RenderWindow &window);

    FloatRect getRect() const { return {x, y, h, w}; };

};

#endif //DELETEDGAME_BULLET_H
