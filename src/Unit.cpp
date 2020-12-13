//
// Created by mi on 23.11.2020.
//

#include "../include/Unit.h"
#include <cmath>

Unit::Unit(Level &level, std::string &name, std::string &fileName, float x, float y, float w, float h, myView &view)
        : FieldObject(level, name, fileName, x, y, w, h) {
    isAlive = true;
    isMove = false;
    isSelect = false;
    basicStats = {
            {"maxHealth", 500},
            {"health",    500},
            {"time",      100000},
            {"maxTime",   100000},
            {"timeStep",  20},
            {"radius",    100}
    };
    dx = 0;
    dy = 0;
    speed = 0;
    dir = 0;
    this->view = view;
    tempX = 0;
    tempY = 0;
    this->map = level.getAllStaticObjects();
}

void Unit::update(float time) {
    if (basicStats["time"] > 0) {
        //control(time);
        switch (dir) {
            case 0:
                dx = -speed;
                dy = 0;
                break;
            case 1:
                dx = speed;
                dy = 0;
                break;
            case 2:
                dx = 0;
                dy = -speed;
                break;
            case 3:
                dx = 0;
                dy = speed;
        }
        x += dx * time;
        interactionWithMap(dx, 0);
        y += dy * time;
        interactionWithMap(0, dy);
        if (!isMove) speed = 0;
        sprite.setPosition(x, y);
    }
    if (basicStats["health"] <= 0) {
        isAlive = false;
        sprite.setColor(Color::Red);
    }
    if (basicStats["time"] <= 0) {
        isMove = false;
        sprite.setColor(Color::Yellow);
    }
}

void Unit::interactionWithMap(float Dx, float Dy) {
    for (auto &i:map)
        if (getRect().intersects(i.rect)) {
            if (i.name == "solid" || i.name == "glass" || i.name == "part") {
                if (Dy > 0) {
                    y = i.rect.top - h;
                    dy = 0;
                }
                if (Dy < 0) {
                    y = i.rect.top + i.rect.height;
                    dy = 0;
                }
                if (Dx > 0) {
                    x = i.rect.left - w;
                }
                if (Dx < 0) {
                    x = i.rect.left + i.rect.width;
                }
            }
        }

}

void Unit::doStep(float time) {
    float distance = 0;
    float timePoints = 0;
    distance = sqrt((tempX - x) * (tempX - x) + (tempY - y) * (tempY -
                                                               y));//считаем дистанцию (расстояние от точки А до точки Б). используя формулу длины вектора
    float tga = tan((tempY - y) / (tempX - x));
    if (distance > 2 && basicStats["time"] > 0) {
        x += 0.1 * time * (tempX - x) / distance;//идем по иксу с помощью вектора нормали
        y += 0.1 * time * (tempY - y) / distance;//идем по игреку так же
        for (auto &i:map) {
            if (getRect().intersects(i.rect)) {
                distance -= sqrt((h + i.rect.height) * (h + i.rect.height) +
                                 (w + i.rect.height / tga) * (w + i.rect.height / tga));
            }
        }
    } else {
        isMove = false;
        std::cout << "priehali\n";
    }//говорим что уже никуда не идем и выводим веселое сообщение в консоль
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
                    isSelect = false;//объект уже не выбран
                    sprite.setColor(Color::White);//возвращаем обычный цвет спрайту
                    tempX = pos.x;//забираем координату нажатия курсора Х
                    tempY = pos.y;//и Y
                }
            }
        }
    }
}

void Unit::control(float time) {
    if (isAlive) {
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            sprite.setOrigin({30, 0});
            sprite.setScale({-1, 1});
            dir = 0;
            speed = 0.1;
            currentFrame += 0.005 * time;
            if (currentFrame > 3) currentFrame -= 3;
            sprite.setTextureRect(IntRect(w * int(currentFrame), 0, w, 50));
            view.getplayercoordforview(x, y);
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            sprite.setScale({1, 1});
            sprite.setOrigin({0, 0});
            dir = 1;
            speed = 0.1;
            currentFrame += 0.005 * time;
            if (currentFrame > 3) currentFrame -= 3;
            sprite.setTextureRect(IntRect(this->w * int(currentFrame), 0, w, 50));
            view.getplayercoordforview(x, y);
        }

        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            dir = 2;
            speed = 0.1;
            currentFrame += 0.005 * time;
            if (currentFrame > 3) currentFrame -= 3;
            sprite.setTextureRect(IntRect(w * int(currentFrame), 0, w, 50));
            view.getplayercoordforview(x, y);
        }

        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            dir = 3;
            speed = 0.1;
            currentFrame += 0.005 * time;
            if (currentFrame > 3) currentFrame -= 3;
            sprite.setTextureRect(IntRect(w * int(currentFrame), 0, w, 50));
            view.getplayercoordforview(x, y);
        }

    }
}

void Unit::acceptDamage(Unit &from) {

}
