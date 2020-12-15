//
// Created by valeria on 25.11.2020.
//

#include "../include/DeletedGame.h"

myView mapView;

DeletedGame::DeletedGame() : window() {}

DeletedGame::~DeletedGame() = default;

void DeletedGame::Init() {
    window.create(sf::VideoMode(1500, 1500), "DeletedGame");
    mapView.view.reset(FloatRect(0, 0, 1000, 800));
}

void DeletedGame::Run() {
    Level level;
    level.loadStaticObjects("../res/map.tmx");
    level.loadDynamicObjects("../res/objects.xml");
    Clock clock, itemsClock, heroClock, enemyClock, attackClock;
    std::list<Item *> itemsList;
    std::list<Hero *> heroList;
    std::list<Unit *> enemyList;
    std::vector<FieldObject *> collectPoints;
    std::vector<Bullet *> bullets;
    for (auto i:level.getStaticObjectsByName("collect")) {
        collectPoints.push_back(
                new FieldObject(level, i.name, i.imagePath, i.rect.left, i.rect.top, i.rect.width, i.rect.height));
    }
    for (auto i:level.getObjectsByType("hero")) {
        heroList.push_back(
                new Hero(level, std::stof(i.properties["precision"]), i.name, i.imagePath, i.rect.left, i.rect.top,
                         i.rect.width, i.rect.height, mapView));
    }
    for (auto i:level.getObjectsByType("enemy")) {
        if (i.subType == "forager_enemy") {
            enemyList.push_back(
                    (Unit *) new ForagerEnemy(level, collectPoints, i.name, i.imagePath, i.rect.left, i.rect.top,
                                              i.rect.width, i.rect.height, mapView));
        }
        if (i.subType == "clever_enemy") {
            enemyList.push_back(
                    (Unit *) new CleverEnemy(level, collectPoints, std::stof(i.properties["precision"]), i.name,
                                             i.imagePath, i.rect.left, i.rect.top, i.rect.width, i.rect.height,
                                             mapView));
        }
        if (i.subType == "wild_enemy") {
            enemyList.push_back((Unit *) new WildEnemy(level, std::stof(i.properties["precision"]),
                                                       std::stof(i.properties["damage"]), i.name, i.imagePath,
                                                       i.rect.left, i.rect.top, i.rect.width, i.rect.height, mapView));
        }

    }
    for (auto i : level.getObjectsByType("item")) {
        if (i.subType == "weapon") {
            itemsList.push_back(
                    (Item *) new Weapon(level, std::stof(i.properties["damage"]), std::stof(i.properties["time_shoot"]),
                                        std::stof(i.properties["time_charge"]), std::stoi(i.properties["bulletType"]),
                                        std::stoi(i.properties["maxbullets"]), std::stoi(i.properties["weight"]),
                                        i.name, i.imagePath,
                                        i.rect.left, i.rect.top, i.rect.width, i.rect.height));
        }
        if (i.subType == "medchest") {
            itemsList.push_back(
                    (Item *) new MedChest(level, std::stof(i.properties["time_rec"]), std::stof(i.properties["hp"]),
                                          std::stoi(i.properties["weight"]), i.name, i.imagePath,
                                          i.rect.left, i.rect.top, i.rect.width, i.rect.height));
        }
        if (i.subType == "bullet_case") {
            itemsList.push_back(
                    (Item *) new BulletCase(level, std::stoi(i.properties["maxbullets"]),
                                            std::stoi(i.properties["bulletType"]),
                                            std::stoi(i.properties["weight"]), i.name, i.imagePath,
                                            i.rect.left, i.rect.top, i.rect.width, i.rect.height));
        }
    }

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
        clock.restart(); //перезагружает время
        time = time / 800;

        Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
        Vector2f pos = window.mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)

        std::cout << pixelPos.x
                  << "\n";//смотрим на координату Х позиции курсора в консоли (она не будет больше ширины окна)
        std::cout << pos.x << "\n";//смотрим на Х,которая преобразовалась в мировые координаты
        Unit *selectedUnit = nullptr;
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                //обрабатываем в цикле событий, иначе потом будет литься куча пуль
                if (event.key.code == sf::Keyboard::Space) {
                    Bullet *bull = new Bullet(level, 500, 500, pos.x,
                                              pos.y);//cоздаю пулю - пока нет ружья, стреляем из точки (100,100)
                    bullets.push_back(bull);//кладем в вектор
                }
            }
        }

        for (auto it = heroList.begin(); it != heroList.end(); it++) {
            Hero *b = *it;
            if (!b->isAlive) {
                it = heroList.erase(it);
                delete b;
            }
            b->toSelect(pos, event);
            if (b->isMove) {
                b->doStep(time);
                mapView.getplayercoordforview(b->x, b->y);

            }
            for (auto item: itemsList) {
                if (b->getRect().intersects(item->getRect()) && item->state == Item::STATE::onMap) {
                    if (Keyboard::isKeyPressed(Keyboard::T)) {
                        b->takeItem(item);
                    }
                }

            }


        }
        for (auto it = enemyList.begin(); it != enemyList.end(); it++) {
            Unit *b = *it;
            if (!b->isAlive) {
                it = enemyList.erase(it);
                delete b;
            }
            b->toSelect(pos, event);
            if (b->isMove) {
                b->doStep(time);
                mapView.getplayercoordforview(b->x, b->y);
                b->basicStats["time"] -= b->basicStats["timeStep"];
            }
            for (auto item: itemsList) {
                if (dynamic_cast<ItemCollector *>(b) != nullptr) {
                    if (b->getRect().intersects(item->getRect()) && item->state == Item::STATE::onMap) {
                        if (Keyboard::isKeyPressed(Keyboard::T)) {
                            dynamic_cast<ItemCollector *>(b)->takeItem(item);
                        }
                    }
                }

            }

        }

        for (auto item = itemsList.begin(); item != itemsList.end(); item++) {

        }
        window.clear();
        mapView.viewMap(time);
        mapView.changeView();
        window.setView(mapView.view);
        level.draw(window);

        for (auto item: itemsList) {
            if (item->state == Item::onMap) {
                item->update(time);
                item->draw(window);
            }
        }
        for (auto hero: heroList) {
            if (hero->isAlive) {
                hero->draw(window);
                hero->update(time);
            }
        }
        for (auto enemy: enemyList) {
            if (enemy->isAlive) {
                enemy->draw(window);
                enemy->update(time);
            }
        }
        for (auto b:bullets) {
            if (b->isAlive) {
                b->doShoot(time);
                b->draw(window);
                b->update(time);
            }
        }
        window.display();
    }
}

