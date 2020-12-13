//
// Created by mi on 22.11.2020.
//

#ifndef GAME_HERO_H
#define GAME_HERO_H

#include "ItemCollector.h"
#include "Shooter.h"

class Hero : public Shooter, public ItemCollector {
private:
    int weight;
    int maxWeight;
public:
    Hero(Level &level, float shootPrecision, std::string &name, std::string &fileName, float x, float y, float w,
         float h, myView &view);

    void activateWeapon(Weapon *w);//в героя
    void recharge(BulletCase *bulletCase);

    void useMedecine(MedChest *med);

    virtual void takeItem(Item *item) override;

    virtual void throwItem(Item *item) override;

    virtual void throwWeapon(Weapon *weapon);

    virtual void takeWeapon(Weapon *weapon) override;

    //float getValueDamage();//урон у ружья
    int getWeight() const { return weight; };

    int getmaxWeight() const { return maxWeight; };

    void setWeight(int weight) { this->weight = weight; };

};

#endif //GAME_HERO_H
