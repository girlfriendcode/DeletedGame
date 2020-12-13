//
// Created by valeria on 02.12.2020.
//

#include "../include/MedChest.h"

MedChest::MedChest(Level &level, float time, float hpExtra, int weight, std::string &name, std::string &fileName,
                   float x, float y, float w,
                   float h) : Item(level, weight, name, fileName, x, y, w, h) {
    this->timeRecovery = time; //time=15.0
    this->hpExtra = hpExtra;
}

