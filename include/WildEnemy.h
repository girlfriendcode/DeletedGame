//
// Created by mi on 22.11.2020.
//

#ifndef GAME_WILDENEMY_H
#define GAME_WILDENEMY_H

#include "Unit.h"
#include "../include/Hero.h"
class WildEnemy : public Unit {
private:
    float precision;
    float damage;
public:
    WildEnemy(Level &level, float precision, float damage, std::string &name, std::string &fileName, float x, float y,
              float w, float h, myView &view);

    //void makeDamage(Hero *hero);
    float getPrecision() const { return precision; };

    virtual float getDamage() const { return damage; };

};


#endif //GAME_WILDENEMY_H
