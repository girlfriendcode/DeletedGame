

#include "../include/WildEnemy.h"


WildEnemy::WildEnemy(Level &level, float precision, float damage, std::string &name, std::string &fileName, float x,
                     float y, float w,
                     float h, myView &view, std::map<std::string, std::string> properties) : Unit(level, name, fileName,
                                                                                                  x, y, w, h, view,
                                                                                                  properties) {
    this->precision = precision;
    this->damage = damage;
}

void WildEnemy::makeDamage(Hero *hero) {
    if (basicStats["time"] >= 0) {
        hero->basicStats["health"] -= damage;
        basicStats["time"] -= 205;
        hero->sprite.setColor(Color::Red);
    }
}

