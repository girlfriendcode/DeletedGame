//
// Created by valeria on 02.12.2020.
//

#ifndef DELETEDGAME_MAPOBJECT_H
#define DELETEDGAME_MAPOBJECT_H

#include <iostream>
#include "main.h"
/**
 * Класс объекта карты для сериализации данных с XML-файла
 */
class MapObject {
public:
    //класс для десериализации
    std::string name;
    std::string type;
    std::string subType;
    std::string imagePath;
    sf::Rect<float> rect;
    std::map<std::string, std::string> properties;
    sf::Sprite sprite;

};

#endif //DELETEDGAME_MAPOBJECT_H
