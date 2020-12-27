#ifndef GAME_ITEM_H
#define GAME_ITEM_H

#include "FieldObject.h"
/**
 * Абстрактный класс вещи
 */
class Item : public FieldObject {

protected:
    int weight;
public :
    enum STATE {
        onMap,
        onInvent,
        nowhere
    };
    STATE state;

    Item(Level &level, int weight, std::string &name, std::string &fileName, float x, float y, float w, float h);

    int getWeight() { return weight; };

    void setWeight(int w) { this->weight = w; };
    virtual FloatRect getRect() override;

    void draw(sf::RenderWindow &window);
    //когда берут вещь, она должна исчезнуть c карты
    //virtual void disappear();//исчезнуть при взятии
    //объекты могут возвращаться следующим образом: у них состояние становится noWhere, удаляется из инвентаря и отрисовка на карте
    //удаляться -таким же образом , только не возвращается на карту и удаляется из вектора объектов карты
};

#endif //GAME_ITEM_H
