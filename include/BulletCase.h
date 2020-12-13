//
// Created by valeria on 27.11.2020.
//

#ifndef DELETEDGAME_BULLETCASE_H
#define DELETEDGAME_BULLETCASE_H

#include "Item.h"
#include "Weapon.h"

class BulletCase : public Item {
private:
    int bullets;
    int maxBullets;
public:
    BulletCase(Level &level, int maxB, int type, int weight, std::string &name, std::string &fileName, float x, float y,
               float w, float h);

    enum BULLETTYPE {
        RIFFLE = 1,
        AUTO = 2,
        PISTOL = 3
    };
    //pistol 45
    BULLETTYPE bulletType;

    int getBullets() const { return bullets; };

    int getMaxBullets() const { return maxBullets; };

    void setBullets(int num) { this->bullets = num; };
    //тоже удаляется из инвентаря , когда пули кончаются

};

#endif //DELETEDGAME_BULLETCASE_H
