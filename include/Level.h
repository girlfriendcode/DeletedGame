
#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <iostream>
#include <vector>
#include "MapObject.h"
#include "Layer.h"
#include "main.h"
#include "string.h"
#include "../include/TinyXML/tinyxml.h"

/**
 * Класс, характеризующий уровень в игре
 */
class Level {
private:
    int width, height, tileWidth, tileHeight, objectTileWidth, objectTileHeight;
    //карта
    int firstTileID;
    std::vector<MapObject> dynamicObjects;
    std::vector<MapObject> staticObjects;
    std::vector<Layer> layers;//cлои тайлов и объектов из tmx
    sf::Texture tilesetImage;
    sf::Texture itemtilesetImage;
public:
    int getWidth() const { return width; };

    int getHeight() const { return height; };

    void setWidth(int w) { this->width = w; };

    void setHeight(int h) { this->height = h; };

    /**
     *
     * @return все статические объекты уровня
     */
    std::vector<MapObject> getAllStaticObjects() { return staticObjects; };

    /**
      *
      * @return все динамические объекты уровня
      */
    std::vector<MapObject> getAllDynamicObjects() { return dynamicObjects; };

    /**
     *
     * Отрисовка уровня
     */
    void draw(sf::RenderWindow &window);

    /**
     *
     * @param fileName -путь к файлу в общей с картой папке
     * Загрузка карты и её текстуры
     */
    bool loadStaticObjects(const std::string &fileName);

    /**
     *
     * @param fileName -путь к файлу в общей с картой папке
     * Загрузка юнитов и предметов
     */
    bool loadDynamicObjects(const std::string &fileName);

    /**
     *
     * @param name имя объекта
     * @return объект по имени
     */
    MapObject getObjectByName(const std::string &name);

    /**
     *
     * @param type тип объекта
     * @return все объекты данного типа
     */
    std::vector<MapObject> getObjectsByType(const std::string &type);

    /**
     *
     * @return все объекты поля данного типа
     */
    std::vector<MapObject> getStaticObjectsByName(const std::string &name);


};

#endif //GAME_LEVEL_H
