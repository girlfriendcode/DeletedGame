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
#include "../include/Inventory.h"
#include "../include/Bullet.h"

using namespace sf;

/**
 * Класс, отвечающий за работку приложения
 */
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

    /**
     * Считаем сумму очков времени команды
     * @param units
     * @return общее число очков
     */

    template<typename T>
    float getSumOfTimePoints(std::list<T *> units) {
        float sum = 0;
        for (auto i:units) {
            sum += i->basicStats["time"];
        }
        return sum;
    }

    /**
     * Обновление очков времени команды
     * @tparam T
     * @param units
     */
    template<typename T>
    void updateSquadTime(std::list<T *> units) {
        for (auto i:units) {
            i->basicStats["time"] = i->basicStats["maxTime"];
            i->sprite.setColor(Color::White);
        }
    }
};

#endif //DELETEDGAME_DELETEDGAME_H
