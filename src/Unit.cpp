//
// Created by mi on 23.11.2020.
//

#include "../include/Unit.h"
#include <cmath>


Unit::Unit(Level &level, std::string &name, std::string &fileName, float x, float y, float w, float h, myView &view,
           std::map<std::string, std::string> properties)
        : FieldObject(level, name, fileName, x, y, w, h) {
    isAlive = true;
    isMove = false;
    isSelect = false;
    /*
    basicStats = {
            {"maxHealth", 100},
            {"health",    100},
            {"time",      5000},
            {"maxTime",   5000},
            {"timeStep",  20},
            {"radius",    100}
    };*/
    basicStats = {
            {"maxHealth", std::stof(properties["maxHealth"])},
            {"health",    std::stof(properties["health"])},
            {"time",      std::stof(properties["time"])},
            {"maxTime",   std::stof(properties["maxTime"])},
            {"timeStep",  std::stof(properties["timeStep"])},
            {"radius",    std::stof(properties["radius"])}
    };
    this->view = view;
    tempX = 0;
    tempY = 0;
    this->map = level.getAllStaticObjects();
}

void Unit::update(float time) {
    if (basicStats["time"] > 0) {
        sprite.setPosition(x, y);
    }
    if (basicStats["health"] <= 0) {
        isAlive = false;
    }
    if (basicStats["time"] <= 0) {
        isMove = false;
        //sprite.setColor(Color::Yellow);
    }
}


void Unit::doStep(float time) {
    isSelect = false;
    float distance = 0;
    float timePoints = 0;
    distance = sqrt((tempX - x) * (tempX - x) + (tempY - y) * (tempY -
                                                               y));//считаем дистанцию (расстояние от точки А до точки Б). используя формулу длины вектора
    float tga = tan((tempY - y) / (tempX - x));
    if (distance > 2 && basicStats["time"] > 0) {
        x += 0.13 * time * (tempX - x) /
             distance;//идем по иксу с помощью вектора нормали 0.13-что-то вроде скорости, чтобы замедлить спрайт
        y += 0.13 * time * (tempY - y) / distance;//идем по игреку так же
        basicStats["time"] -= basicStats["timeStep"] * distance / 200;
        for (auto &i:map) {
            if (getRect().intersects(i.rect)) {
                distance -= sqrt((h + i.rect.height) * (h + i.rect.height) +
                                 (w + i.rect.height / tga) * (w + i.rect.height / tga));
                if (i.rect.width >= i.rect.height) {
                    if (tempY - y > 0) {
                        y -= i.rect.height / 3;
                    } else {
                        y += i.rect.height / 3;
                    }
                } else {
                    if (tempX - x > 0) {
                        x -= i.rect.width / 3;
                    } else {
                        x += i.rect.width / 3;
                    }
                }
                isMove = false;
            }
        }

    } else {
        isMove = false;
        std::cout << "priehali\n";
    }//говорим что уже никуда не идем и выводим сообщение в консоль
}

void Unit::toSelect(Vector2f pos, sf::Event event) {
    if (event.type == Event::MouseButtonPressed) {//если нажата клавиша мыши
        if (event.key.code == Mouse::Left) {//а именно левая
            if (sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
            {
                sprite.setColor(Color::Green);
                isSelect = true;
            }
        }
        if (isSelect) {
            if (event.type == Event::MouseButtonPressed) {//если нажата клавиша мыши
                if (event.key.code == Mouse::Right) {//а именно правая
                    isMove = true;//то начинаем движение
                    sprite.setColor(Color::White);//возвращаем обычный цвет спрайту
                    tempX = pos.x;//забираем координату нажатия курсора Х
                    tempY = pos.y;//и Y
                }
            }
        }
    }
}

