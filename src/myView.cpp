//
// Created by valeria on 07.12.2020.
//
#include "../include/myView.h"

void myView::viewMap(float time) {
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        view.move(0.07 * time, 0);//скроллим карту вправо (см урок, когда мы двигали героя - всё тоже самое)
    }

    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        view.move(0, 0.07 * time);//скроллим карту вниз (см урок, когда мы двигали героя - всё тоже самое)
    }

    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        view.move(-0.07 * time, 0);//скроллим карту влево (см урок, когда мы двигали героя - всё тоже самое)
    }
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        view.move(0, -0.07 * time);//скроллим карту вправо (см урок, когда мы двигали героя - всё тоже самое)
    }
}

void myView::getplayercoordforview(int x, int y) {
    float tempX = x;
    float tempY = y;
    if (x > 1000) tempX = 1000;
    if (x < 600) tempX = 600;
    if (y > 750) tempY = 750;
    if (y < 400) tempY = 400;

    view.setCenter(tempX, tempY);
}

void myView::changeView() {
    if (Keyboard::isKeyPressed(Keyboard::LBracket)) {
        view.zoom(0.9994); //масштабируем, уменьшение
    }
    if (Keyboard::isKeyPressed(Keyboard::RBracket)) {
        view.zoom(1.0006f); //масштабируем, приближение
    }

    if (Keyboard::isKeyPressed(Keyboard::Z)) {
        view.setSize(1000, 800);//устанавливает размер камеры (наш исходный)
    }

}
