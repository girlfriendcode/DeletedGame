//
// Created by valeria on 25.11.2020.
//

#ifndef DELETEDGAME_DELETEDGAME_H
#define DELETEDGAME_DELETEDGAME_H

#include "myView.h"
#include "../include/Level.h"
#include "../include/Hero.h"
#include "../include/Item.h"
#include "../include/WildEnemy.h"
#include "../include/ForagerEnemy.h"
#include "../include/CleverEnemy.h"
#include <cmath>
#include <list>
#include "../include/myView.h"
#include "../include/TinyXML/tinyxml.h"
#include "../include/Weapon.h"
#include "../include/MedChest.h"
#include "../include/BulletCase.h"

using namespace sf;

class DeletedGame {
protected:
    sf::RenderWindow window;
public:
    DeletedGame();

    ~DeletedGame();

    /**
     * Создание окна игры
     */
    void Init();

    /**
     * Загрузка карты и игровой процесс
     */
    void Run();


};

#endif //DELETEDGAME_DELETEDGAME_H
