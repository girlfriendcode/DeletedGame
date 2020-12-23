//
// Created by mi on 22.11.2020.
//

#ifndef GAME_WEAPON_H
#define GAME_WEAPON_H

#include "Item.h"
/**
 * Класс оружия
 */

class Weapon : public Item {
private:
    float w_damage;
    /**
     * Время, затрачиваемое на стрельбу
     */
    float timeShoot;//определяю тут
    /**
     * Время, затрачиваемое на перезарядку
     */
    float timeCharge;//определяю тут
    int maxBullets;
    int bullets;// может меняться в процессе
    //ружье весит 5
public:
    /**
     * Тип оружия
     */
    enum BULLETTYPE {
        RIFFLE = 1,
        AUTO = 2,
        PISTOL = 3
    };
    BULLETTYPE bulletType;

    Weapon(Level &level, float damage, float tshoot, float tcharge, int type, int maxB, int weight, std::string &name,
           std::string &fileName, float x, float y, float w, float h);

    float getW_Damage() const { return w_damage * bulletType; };

    float gettimeShoot() const { return timeShoot; };

    float gettimeCharge() const { return timeCharge; };

    int getmaxBullets() const { return maxBullets; };

    int getBullets() const { return bullets; };

    void setBullets(int bullets) { this->bullets = bullets; };
    //calculate charge time

};


#endif //GAME_WEAPON_H
