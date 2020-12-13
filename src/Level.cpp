//
// Created by mi on 23.11.2020.
//

#include "../include/Level.h"

#include "../include/MapObject.h"

void Level::draw(sf::RenderWindow &window) {
    for (auto &layer : layers)
        for (const auto &tile : layer.tiles)
            window.draw(tile);
}

MapObject Level::getObjectByName(const std::string &name) {
    for (auto &object : dynamicObjects) {
        if (object.name == name)
            return object;
    }
}

std::vector<MapObject> Level::getObjectsByType(const std::string &type) {
    std::vector<MapObject> vec;
    for (auto &object:dynamicObjects)
        if (object.type == type)
            vec.push_back(object);
    return vec;
}

std::vector<MapObject> Level::getStaticObjectsByName(const std::string &name) {
    std::vector<MapObject> vec;
    for (auto &object:staticObjects)
        if (object.name == name)
            vec.push_back(object);
    return vec;
}


bool Level::loadStaticObjects(const std::string &fileName) {
    TiXmlDocument levelFile(fileName.c_str());

    // Загружаем XML-карту
    if (!levelFile.LoadFile()) {
        std::cout << "Loading level \"" << fileName << "\" failed." << std::endl;
        return false;
    }

    // Работаем с контейнером map
    TiXmlElement *map;
    map = levelFile.FirstChildElement("map");

    width = atoi(map->Attribute("width"));
    height = atoi(map->Attribute("height"));
    tileWidth = atoi(map->Attribute("tilewidth"));
    tileHeight = atoi(map->Attribute("tileheight"));

    // Берем описание тайлсета и идентификатор первого тайла
    TiXmlElement *tilesetElement;
    tilesetElement = map->FirstChildElement("tileset");
    firstTileID = atoi(tilesetElement->Attribute("firstgid"));

    // source - путь до картинки в контейнере image
    TiXmlElement *image;
    image = tilesetElement->FirstChildElement("image");
    std::string imagepath = image->Attribute("source");

    // Пытаемся загрузить тайлсет
    sf::Image img;

    if (!img.loadFromFile("../res/" + imagepath)) {
        std::cout << "Failed to load tile sheet." << std::endl;
        return false;
    }

    // Очищаем карту от света (109, 159, 185)
    // Вообще-то в тайлсете может быть фон любого цвета, но я не нашел решения, как 16-ричную строку
    // вроде "6d9fb9" преобразовать в цвет
    img.createMaskFromColor(sf::Color(109, 159, 185));
    // Грузим текстуру из изображения
    tilesetImage.loadFromImage(img);
    // Расплывчатость запрещена
    tilesetImage.setSmooth(false);

    // Получаем количество столбцов и строк тайлсета
    int columns = tilesetImage.getSize().x / tileWidth;
    int rows = tilesetImage.getSize().y / tileHeight;

    // Вектор из прямоугольников изображений (TextureRect)
    std::vector<sf::Rect<int>> subRects;

    for (int y = 0; y < rows; y++)
        for (int x = 0; x < columns; x++) {
            sf::Rect<int> rect;

            rect.top = y * tileHeight;
            rect.height = tileHeight;
            rect.left = x * tileWidth;
            rect.width = tileWidth;

            subRects.push_back(rect);
        }

    // Работа со слоями
    TiXmlElement *layerElement;
    layerElement = map->FirstChildElement("layer");
    while (layerElement) {
        Layer layer;

        // Если присутствует opacity, то задаем прозрачность слоя, иначе он полностью непрозрачен
        if (layerElement->Attribute("opacity") != NULL) {
            float opacity = strtod(layerElement->Attribute("opacity"), NULL);
            layer.opacity = 255 * opacity;
        } else {
            layer.opacity = 255;
        }

        // Контейнер <data>
        TiXmlElement *layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        if (layerDataElement == NULL) {
            std::cout << "Bad map. No layer information found." << std::endl;
        }

        // Контейнер <tile> - описание тайлов каждого слоя
        TiXmlElement *tileElement;
        tileElement = layerDataElement->FirstChildElement("tile");

        if (tileElement == NULL) {
            std::cout << "Bad map. No tile information found." << std::endl;
            return false;
        }

        int x = 0;
        int y = 0;

        while (tileElement) {
            int tileGID = atoi(tileElement->Attribute("gid"));
            int subRectToUse = tileGID - firstTileID;

            // Устанавливаем TextureRect каждого тайла
            if (subRectToUse >= 0) {
                sf::Sprite sprite;
                sprite.setTexture(tilesetImage);
                sprite.setTextureRect(subRects[subRectToUse]);
                sprite.setPosition(x * tileWidth, y * tileHeight);
                sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

                layer.tiles.push_back(sprite);
            }

            tileElement = tileElement->NextSiblingElement("tile");

            x++;
            if (x >= width) {
                x = 0;
                y++;
                if (y >= height)
                    y = 0;
            }
        }

        layers.push_back(layer);

        layerElement = layerElement->NextSiblingElement("layer");
    }

    // Работа с объектами
    TiXmlElement *objectGroupElement;

    // Если есть слои объектов
    if (map->FirstChildElement("objectgroup") != NULL) {
        objectGroupElement = map->FirstChildElement("objectgroup");
        while (objectGroupElement) {
            // Контейнер <object>
            TiXmlElement *objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");

            while (objectElement) {
                // Получаем все данные - тип, имя, позиция, etc
                std::string objectType;
                if (objectElement->Attribute("type") != NULL) {
                    objectType = objectElement->Attribute("type");
                }
                std::string objectName;
                if (objectElement->Attribute("name") != NULL) {
                    objectName = objectElement->Attribute("name");
                }
                int x = atoi(objectElement->Attribute("x"));
                int y = atoi(objectElement->Attribute("y"));

                int width, height;

                sf::Sprite sprite;
                sprite.setTexture(tilesetImage);
                sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
                sprite.setPosition(x, y);

                if (objectElement->Attribute("width") != NULL) {
                    width = atoi(objectElement->Attribute("width"));
                    height = atoi(objectElement->Attribute("height"));
                } else {
                    width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
                    height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
                    sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
                }

                // Экземпляр объекта
                MapObject object;
                object.name = objectName;
                object.type = objectType;
                object.sprite = sprite;


                sf::Rect<float> objectRect;
                objectRect.top = y;
                objectRect.left = x;
                objectRect.height = height;
                objectRect.width = width;
                object.rect = objectRect;

                // "Переменные" объекта
                TiXmlElement *properties;
                properties = objectElement->FirstChildElement("properties");
                if (properties != NULL) {
                    TiXmlElement *prop;
                    prop = properties->FirstChildElement("property");
                    if (prop != NULL) {
                        while (prop) {
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");

                            object.properties[propertyName] = propertyValue;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }

                // Пихаем объект в вектор
                staticObjects.push_back(object);

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    } else {
        std::cout << "No object layers found..." << std::endl;
    }

    return true;

}

bool Level::loadDynamicObjects(const std::string &filename) {
    TiXmlDocument stateFile(filename.c_str());

    // Загружаем XML
    if (!stateFile.LoadFile()) {
        std::cout << "Loading state of \"" << filename << "\" failed." << std::endl;
        return false;
    }

    TiXmlElement *map = stateFile.FirstChildElement("map"); // загрузил карту объектов
    TiXmlElement *image = map->FirstChildElement("image"); // загрузил тайлсет объектов
    objectTileWidth = atoi(image->Attribute("tileWidth"));
    objectTileHeight = atoi(image->Attribute("tileHeight"));

    std::string imagePath = image->Attribute("source");

    // путь к тайлсету предметов, загрузка
    sf::Image img;
    if (!img.loadFromFile("../res/" + imagePath)) {
        std::cout << "Failed to load tile sheet." << std::endl;
        return false;
    } else {
        std::cout << "Items tiles loaded successfully." << std::endl;
    }

    img.createMaskFromColor(sf::Color(255, 255, 255));
    itemtilesetImage.loadFromImage(img);
    itemtilesetImage.setSmooth(true);

    // Получаем количество столбцов и строк тайлсета
    int columns = itemtilesetImage.getSize().x / objectTileWidth;
    int rows = itemtilesetImage.getSize().y / objectTileHeight;

    // Вектор из прямоугольников изображений предметов (TextureRect)
    std::vector<sf::Rect<int> > subRects;

    for (int y = 0; y < rows; y++)
        for (int x = 0; x < columns; x++) {
            sf::Rect<int> rect;

            rect.top = y * objectTileHeight;
            rect.height = objectTileHeight;
            rect.left = x * objectTileWidth;
            rect.width = objectTileWidth;

            subRects.push_back(rect);
        }

    // Работа с объектами
    TiXmlElement *objectGroupElement;

    // Если есть слои объектов
    if (map->FirstChildElement("objectgroup") != nullptr) {
        objectGroupElement = map->FirstChildElement("objectgroup");

        // идём по слоям объектов
        while (objectGroupElement) {
            // Контейнер <object>
            TiXmlElement *objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");

            std::vector<MapObject> currLayerObjects; // список объектов текущего слоя

            while (objectElement) {
                // Получаем все данные - тип, подтип, имя, позиция
                std::string objectType;
                if (objectElement->Attribute("type") != nullptr) {
                    objectType = objectElement->Attribute("type");
                }
                std::string objectSubType;
                if (objectElement->Attribute("subType") != nullptr) {
                    objectSubType = objectElement->Attribute("subType");
                }
                std::string objectName;
                if (objectElement->Attribute("name") != nullptr) {
                    objectName = objectElement->Attribute("name");
                }
                int layer;
                if (objectElement->Attribute("layer") != nullptr) {
                    layer = atoi(objectElement->Attribute("layer"));
                }

                int x = atoi(objectElement->Attribute("x"));
                int y = atoi(objectElement->Attribute("y"));

                int width, height;
                sf::Sprite sprite;
                sprite.setPosition(x, y);

                if (objectElement->Attribute("width") != nullptr) {
                    width = atoi(objectElement->Attribute("width"));
                    height = atoi(objectElement->Attribute("height"));
                } else {
                    width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
                    height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
                    sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
                }

                sf::Image image;
                sf::Texture texture;

                if (objectType == "hero") {
                    image.loadFromFile("../res/img/hero.png");
                    imagePath = objectName + ".png";
                }
                if (objectType == "enemy") {
                    image.loadFromFile("../res/img/enemies/" + objectName + ".png");
                    imagePath = "enemies/" + objectName + ".png";
                }

                if (objectType == "item" && objectSubType != "weapon") {
                    image.loadFromFile("../res/img/items/" + objectName + ".png");
                    imagePath = "items/" + objectName + ".png";
                }

                if (objectType == "item" && objectSubType == "weapon") {
                    image.loadFromFile("../res/img/items/weapons/" + objectName + ".png");
                    imagePath = "items/weapons/" + objectName + ".png";
                }

                texture.loadFromImage(image);
                sprite.setTexture(texture);
                sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));

                MapObject object;
                object.name = objectName;
                object.type = objectType;
                object.sprite = sprite;
                object.imagePath = imagePath;
                object.subType = objectSubType;


                sf::Rect<float> objectRect;
                objectRect.top = y;
                objectRect.left = x;
                objectRect.height = height;
                objectRect.width = width;
                object.rect = objectRect;

                TiXmlElement *properties; // Переменные объекта
                properties = objectElement->FirstChildElement("properties");
                if (properties != nullptr) {
                    TiXmlElement *prop;
                    prop = properties->FirstChildElement("property");
                    if (prop != nullptr) {
                        while (prop) {
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");
                            object.properties[propertyName] = propertyValue;
                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }

                dynamicObjects.push_back(object);
                objectElement = objectElement->NextSiblingElement("object");
            }

            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    } else {
        std::cout << "No item & unit layers found..." << std::endl;
    }

    return true;
}

