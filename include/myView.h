//
// Created by valeria on 07.12.2020.
//

#ifndef DELETEDGAME_MYVIEW_H
#define DELETEDGAME_MYVIEW_H

#include "main.h"

using namespace sf;
/**
 * Класс камеры, следяющей за игрой
 */
class myView {
public:
    sf::View view;

    /**
     * Получение координаты игрока и установка при краевых x,y
     * @param x
     * @param y
     */
    void getplayercoordforview(int x, int y);

    /**
     * Скролл карты up-down-right-left
     * @param time
     */
    void viewMap(float time);

    /**
     * Зум
     */
    void changeView();
};

#endif //DELETEDGAME_MYVIEW_H
