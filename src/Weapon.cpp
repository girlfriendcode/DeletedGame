//
// Created by valeria on 02.12.2020.
//

#include "../include/Weapon.h"

Weapon::Weapon(Level &level, float damage, float tshoot, float tcharge, int type, int maxB, int weight,
               std::string &name,
               std::string &fileName, float x, float y, float w, float h) : Item(level, weight, name, fileName, x, y, w,
                                                                                 h) {
    this->w_damage = damage;
    this->timeShoot = tshoot;
    this->timeCharge = tcharge;
    this->maxBullets = maxB;
    this->bulletType = static_cast<BULLETTYPE>(type);
    this->bullets = maxB;
}

