//
// Created by valeria on 28.11.2020.
//

#ifndef DELETEDGAME_SHOOTER_H
#define DELETEDGAME_SHOOTER_H

#include "Unit.h"
#include "Weapon.h"
/**
 * Класс стрелка
 */
class Shooter : virtual public Unit {
protected:
    Weapon *activeWeapon;
    float shootPrecision;
public:
    Shooter(Level &level, float precision, std::string &name, std::string &fileName, float x, float y, float w, float h,
            myView &view);

    /**
     * Взять оружие
     * @param w выбранное оружие
     */
    virtual void takeWeapon(Weapon *w);

    /**
     * Сбросить активное оружие
     */
    virtual void throwWeapon();

    float getPrecision() const { return this->shootPrecision; };

    Weapon *getWeapon() const { return this->activeWeapon; };

    /**
     * Функция для вычисления попадания/непопадания в юнит
     * @param distance расстояние между стрелком и целью
     * @return возвращает, удачен или нет выстрел
     */
    bool shootSuccessful(float distance);
    /**
     * Cделать выстрел
     * @param hitUnit
     */
    //virtual void shoot();
    void makeShoot(Unit *hitUnit);
};

#endif //DELETEDGAME_SHOOTER_H
