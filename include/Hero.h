//
// Created by mi on 22.11.2020.
//

#ifndef GAME_HERO_H
#define GAME_HERO_H

#include "ItemCollector.h"
#include "Shooter.h"
/**
 * Класс оперативника(героя)
 */
class Hero : public Shooter, public ItemCollector {
private:
    int weight;
    int maxWeight;

    //MyContainer<Weapon*> weapons;
public:
    Hero(Level &level, float shootPrecision, std::string &name, std::string &fileName, float x, float y, float w,
         float h, myView &view, std::map<std::string, std::string> properties);

    int currItem;

    /**
     * Выбор оружия
     * @param w выбранное оружие
     */
    void activateWeapon(Weapon *w);//в героя
    /**
     * Перезарядка оружия
     * @param bulletCase магазин патронов
     */
    void recharge(BulletCase *bulletCase);

    /**
     * Использовать аптечку
     * @param med аптечка
     */
    void useMedecine(MedChest *med);

    /**
     * Взять вещь с карты
     * @param item
     */
    virtual void takeItem(Item *item) override;

    /**
     * Сбросить выбранный предмет
     * @param item
     */
    virtual void throwItem(Item *item) override;

    virtual void throwItem(float x, float y);

    /**
     * Бросить оружие
     * @param weapon
     */
    virtual void throwWeapon(Weapon *weapon);

    /**
     * Взять оружие
     * @param weapon
     */
    virtual void takeWeapon(Weapon *weapon) override;

    //float getValueDamage();//урон у ружья
    int getWeight() const { return weight; };

    int getmaxWeight() const { return maxWeight; };

    void setWeight(int weight) { this->weight = weight; };

};

#endif //GAME_HERO_H
