//
// Created by mi on 22.11.2020.
//

#ifndef GAME_MEDCHEST_H
#define GAME_MEDCHEST_H
#include "Item.h"
/**
 * Класс аптечки
 */
class MedChest : public Item {
private:
    float timeRecovery;
    float hpExtra;
public:
    MedChest(Level &level, float time, float hpExtra, int weight, std::string &name, std::string &fileName, float x,
             float y, float w, float h);

//аптечка весит 3
    float getHp() const { return hpExtra; };

    void setHpNull() { this->hpExtra = 0; };

    float gettimeRec() const { return timeRecovery; };

};

#endif //GAME_MEDCHEST_H
