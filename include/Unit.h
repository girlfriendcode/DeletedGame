//
// Created by mi on 22.11.2020.
//

#ifndef GAME_UNIT_H
#define GAME_UNIT_H

#include "FieldObject.h"
#include "Item.h"
#include "MapObject.h"
#include "myView.h"
#include "Level.h"

#include <map>

/**
 * Класс, описывающий юнит-двигающийся по полю одушевленный объект
 */
class Unit : public FieldObject {

public:
    /**
     * Общие для всех юнитов характеристики: максимальное и текущее здоровье, максимальное и текущее кол-во очков времени
     * радиус обзора, кол-во очков времени, затрачиваемое на шаг
     */
    std::map<std::string, float> basicStats;
    bool isAlive, isMove, isSelect;
    float dx, dy, speed;//перемещение по х и у в единицу времени
    double currentFrame = 0;
    int dir;
    myView view;
    int tempX, tempY;
    std::vector<MapObject> map;

    Unit(std::string &name, std::string &fileName, float x, float y, float w, float h);

    Unit(Level &level, std::string &name, std::string &fileName, float x, float y, float w, float h, myView &view);

    /**
     * Обновление состояния персонажа
     */

    virtual void update(float time) override;

    /**
     * Обработка столкновений с объектами карты
     * @param Dx
     * @param Dy
     */

    void interactionWithMap(float Dx, float Dy);

    /**
     * Выбор данного юнита
     * @param pos
     * @param event
     */

    void toSelect(Vector2f pos, sf::Event event);

    /**
     * Сделать шаг в место клика курсора
     * @param time
     */
    void doStep(float time);


    void control(float time);
    // virtual void calculateDamage(Unit *unit);
};

#endif //GAME_UNIT_H
