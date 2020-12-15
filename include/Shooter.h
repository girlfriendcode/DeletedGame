//
// Created by valeria on 28.11.2020.
//

#ifndef DELETEDGAME_SHOOTER_H
#define DELETEDGAME_SHOOTER_H

#include "Unit.h"
#include "Weapon.h"

class Shooter : virtual public Unit {
protected:
    Weapon *activeWeapon;
    float shootPrecision;
public:
    Shooter(Level &level, float precision, std::string &name, std::string &fileName, float x, float y, float w, float h,
            myView &view);

    virtual void takeWeapon(Weapon *w);

    virtual void throwWeapon();

    float getPrecision() const { return this->shootPrecision; };

    Weapon *getWeapon() const { return this->activeWeapon; };
    bool shootSuccessful(float distance);

    //virtual void shoot();
    void makeShoot(Unit *hitUnit);
};

#endif //DELETEDGAME_SHOOTER_H
