//
// Created by mi on 22.11.2020.
//

#ifndef GAME_FORAGERENEMY_H
#define GAME_FORAGERENEMY_H

#include "Carrier.h"
#include "ItemCollector.h"
/**
 * Класс фуражира
 */
class ForagerEnemy : public Carrier, public ItemCollector {
public:
    ForagerEnemy(Level &level, std::vector<FieldObject *> points, std::string &name, std::string &fileName, float x,
                 float y, float w, float h, myView &view);
    //cразу все сбрасывает
    //void throwItem(std::vector <Item> itemsTaken, CollectPoint &point);
};

#endif //GAME_FORAGERENEMY_H
