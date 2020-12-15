//
// Created by valeria on 30.11.2020.
//

#include "../include/BulletCase.h"

BulletCase::BulletCase(Level &level, int maxB, int type, int weight, std::string &name, std::string &fileName,
                       float x, float y, float w, float h) : Item(level, weight, name, fileName, x, y, w, h) {
    this->bulletType = static_cast<BULLETTYPE>(type);
    this->maxBullets = maxB;
    this->bullets = maxB;
}


