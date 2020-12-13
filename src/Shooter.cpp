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
    //добавляем на поле назад
}

void Shooter::takeWeapon(Weapon *w) {
    if (activeWeapon != nullptr) {
        Weapon *weaponThrow = activeWeapon;
        //возвращаем на карту
        throwWeapon();//Хотите удалить оружие?(добавить диалог)
    }
    activeWeapon = w;
}


