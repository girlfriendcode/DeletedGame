//
// Created by valeria on 02.12.2020.
//

#include "../include/WildEnemy.h"


WildEnemy::WildEnemy(Level &level, float precision, float damage, std::string &name, std::string &fileName, float x,
                     float y, float w,
                     float h, myView &view) : Unit(level, name, fileName, x, y, w, h, view) {
    this->precision = precision;
    this->damage = damage;
}

void WildEnemy::makeDamage(Hero *hero) {
    hero->basicStats["health"] -= damage;
    basicStats["time"] -= 205;
    hero->sprite.setColor(Color::Red);
}

