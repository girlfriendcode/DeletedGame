//
// Created by valeria on 28.11.2020.
//
#include "../include/Shooter.h"

Shooter::Shooter(Level &level, float precision, std::string &name, std::string &fileName, float x, float y, float w,
                 float h, myView &view) : Unit(level, name, fileName, x, y, w, h, view) {
    this->shootPrecision = precision;
    this->activeWeapon = nullptr;
}

void Shooter::throwWeapon() {
    if (activeWeapon == nullptr) {
        std::cout << "There is nothing to delete!" << std::endl;
        return;
    }
    Weapon *weaponThrow = activeWeapon;
    activeWeapon = nullptr;
    weaponThrow->state = Item::STATE::onMap;
    weaponThrow->x = x - 10;
    weaponThrow->y = y;
    //добавляем на поле назад
}

void Shooter::takeWeapon(Weapon *w) {
    if (activeWeapon != nullptr) {
        Weapon *weaponThrow = activeWeapon;
        //возвращаем на карту
        throwWeapon();//Хотите удалить оружие?(добавить диалог)
    }
    w->state = Item::STATE::onInvent;
    activeWeapon = w;
}

void Shooter::makeShoot(Unit *hitUnit) {
    if (activeWeapon != nullptr) {
        hitUnit->basicStats["health"] -= activeWeapon->getW_Damage();
        basicStats["time"] -= activeWeapon->gettimeShoot();
        int bullets = activeWeapon->getBullets() - 1;
        activeWeapon->setBullets(bullets);
    }
}

bool Shooter::shootSuccessful(float distance) {
    float chance = shootPrecision * 10 / distance;
    float dw = basicStats["radius"] - distance;
    srand(time(0));
    float random = 0.001 + rand() % 300;
    if (random <= chance - dw || random >= chance + dw)return true;
    else return false;
}