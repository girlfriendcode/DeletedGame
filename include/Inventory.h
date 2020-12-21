//
// Created by valeria on 21.12.2020.
//

#ifndef DELETEDGAME_INVENTORY_H
#define DELETEDGAME_INVENTORY_H

#include "main.h"
#include "ItemCollector.h"

class Inventory {
private:
    ItemCollector *itemCollector;
public:
    /**
     * Бар оружия
     */
    sf::RectangleShape weaponsBar;
    /**
     * Бар аптечек и магазинов
     */
    sf::RectangleShape itemsBar;

    Color outLineColor = Color(132, 36, 110);
    Color fillColor = Color(255, 231, 186);


    Font font;

    Inventory();

    /**
     * Отрисовка двух баров
     * m window
     */
    void draw(RenderWindow &window);

    void changeSize(float x, float y);

    /**
     * Получение ссылки на юнит
     */
    void getUnit(ItemCollector *collector) {
        this->itemCollector = collector;
    }

};

#endif //DELETEDGAME_INVENTORY_H
