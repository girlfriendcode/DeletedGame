//
// Created by valeria on 28.11.2020.
//

#ifndef DELETEDGAME_ITEMCOLLECTOR_H
#define DELETEDGAME_ITEMCOLLECTOR_H

#include "Unit.h"
#include "Weapon.h"
#include "BulletCase.h"
#include "MedChest.h"
#include "MyContainer.h"
/**
 * Абстракный класс юнита, у которого есть инвентарь
 */
class ItemCollector : virtual public Unit {

public:
    ItemCollector(Level &level, std::string &name, std::string &fileName, float x, float y, float w, float h,
                  myView &view);

    MyContainer<Item *> inventory;

    virtual void takeItem(Item *item);

    //обработка выбора выброса именно этого предмета
    virtual void throwItem(Item *item);

    /**
     * Cброс всех вещей инвентаря при смерти
     */
    virtual void throwItem();//сброс при смерти одинаков
};

#endif //DELETEDGAME_ITEMCOLLECTOR_H
