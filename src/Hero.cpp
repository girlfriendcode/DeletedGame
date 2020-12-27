//
// Created by mi on 23.11.2020.
//
#pragma once

#include "../include/Hero.h"

Hero::Hero(Level &level, float shootPrecision, std::string &name, std::string &fileName, float x, float y, float w,
           float h, myView &view, std::map<std::string, std::string> properties) : Unit(level, name, fileName, x, y, w,
                                                                                        h, view, properties),
                                                                                   ItemCollector(level, name, fileName,
                                                                                                 x, y, w, h, view,
                                                                                                 properties),
                                                                                   Shooter(level, shootPrecision, name,
                                                                                           fileName, x, y, w, h, view,
                                                                                           properties) {
    this->maxWeight = 20;
    this->weight = 0;
    this->currItem = 0;
}

void Hero::takeItem(Item *item) {
    if (maxWeight < weight + item->getWeight()) return;//dialog
    else {
        inventory.push_back(item);
        item->state = Item::STATE::onInvent;
        weight += item->getWeight();
        //исчезновение вещи c карты

    }
}

void Hero::throwItem(Item *item) {
    ItemCollector::throwItem(item);
    item->state = Item::STATE::onMap;
    this->setWeight(this->getWeight() - item->getWeight());
    //добавляем предмет на поле
}

void Hero::useMedecine(MedChest *med) {
    if (med != nullptr) {
        basicStats["health"] += med->getHp();
        if (basicStats["health"] >= basicStats["maxHealth"])
            basicStats["health"] = basicStats["maxHealth"];
        basicStats["timePoints"] -= med->gettimeRec();
        //аптечка уничтожается
    }
}

void Hero::activateWeapon(Weapon *w) {
    this->activeWeapon = w;
}

void Hero::recharge(BulletCase *bulletCase) {
    if (bulletCase->bulletType == activeWeapon->bulletType) {
        basicStats["timePoints"] -= activeWeapon->gettimeCharge();
        int bulletsInWeapon = activeWeapon->getBullets();
        int bulletsInCase = bulletCase->getBullets();
        int maxWBullet = activeWeapon->getmaxBullets();
        if (maxWBullet < bulletsInWeapon + bulletsInCase) {
            activeWeapon->setBullets(maxWBullet);
            bulletCase->setBullets(bulletsInCase - (maxWBullet - bulletsInWeapon));
        } else {
            activeWeapon->setBullets(bulletsInWeapon + bulletsInCase);
            bulletCase->setBullets(0);
            //удаляется магазин
        }
    }
}

void Hero::takeWeapon(Weapon *weapon) {
    takeItem(weapon);
    if (activeWeapon == nullptr) {
        activeWeapon = weapon;
    }
}

void Hero::throwWeapon(Weapon *weapon) {
    if (activeWeapon == weapon) {
        activeWeapon = nullptr;
        //возвращаем на поле оружие
    }
    throwItem(weapon);
}

void Hero::throwItem(float x, float y) {
    ItemCollector::throwItem(x, y);
}

