//
// Created by valeria on 28.11.2020.
//
#include "../include/Shooter.h"

Shooter::Shooter(Level &level, float precision, std::string &name, std::string &fileName, float x, float y, float w,
                 float h, myView &view, std::map<std::string, std::string> properties) : Unit(level, name, fileName, x,
                                                                                              y, w, h, view,
                                                                                              properties) {
    this->shootPrecision = precision;
    this->activeWeapon = nullptr;
    isShooting = false;
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

void Shooter::makeShoot() {
    basicStats["time"] -= activeWeapon->gettimeShoot();//сделать timeshoot больше
    int bullets = activeWeapon->getBullets() - 1;
    activeWeapon->setBullets(bullets);
}

bool Shooter::shootSuccessful(float distance) {
    float chance = shootPrecision * 10 / distance;
    float dw = basicStats["radius"] - distance;
    srand(time(0));
    float random = 0.001 + rand() % 300;
    if (random <= chance - dw || random >= chance + dw)return true;
    else return false;
}

void Shooter::attack(Unit *unit) {
    unit->basicStats["health"] -= activeWeapon->getW_Damage();
    unit->sprite.setColor(Color::Cyan);
}

void Shooter::update(float time) {
    Unit::update(time);
    if (basicStats["time"] <= 0) {
        isShooting = false;
        //sprite.setColor(Color::Yellow);
    }
}
