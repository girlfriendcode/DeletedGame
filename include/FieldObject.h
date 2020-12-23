#ifndef GAME_FIELDOBJECT_H
#define GAME_FIELDOBJECT_H

#include <iostream>
#include "main.h"
#include "Level.h"

using namespace sf;

/**
 * Класс, описывающий объект карты, имеющий файл текстуры и координаты
 */
using namespace sf;
class FieldObject {
public:
    float x, y, h, w;
    std::string fileName, name, type, subType;
    Level level;
    /**
     * Перечисление видов статическиx объектов карты
     */
    enum staticObjects {
        FLOOR,
        WALL,
        GLASS,
        COLLECT,
        PARTITION
    };
    /**
     * Текстура, спрайт,картинка и шрифт
     */
    Texture texture;
    Sprite sprite;
    Image image;
    Font font;

    FieldObject(Level &level, std::string &name, std::string &fileName, float x, float y, float w, float h);

    FieldObject(std::string &name, std::string &fileName, float x, float y, float w, float h);
    /**
     * Отрисовка объекта
     * @param window-окно, в котором отрисовывается объект
     */
    virtual void draw(RenderWindow &window);//отрисовывает объект в нужном месте
    /**
     * Обновление координаты объекта
     * @param time -счётчик времени
     */
    virtual void update(float time);//обновление состояния объекта
    /**
     *
     * @return четырёхугольник объекта
     */
    virtual FloatRect getRect() const { return {x, y, h, w}; };

    float getX() const { return x; };

    float getY() const { return y; };

};


#endif //GAME_FIELDOBJECT_H
