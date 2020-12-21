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
    Clock clock, itemsClock, attackClock;
    std::list<Item *> itemsList;
    std::list<Hero *> heroList;
    Inventory inventBar;
    sf::RectangleShape shape;
    shape.setPosition(100, 100);
    shape.setSize({100, 100});
    shape.setFillColor(Color::Red);
    std::list<Inventory *> inventList;
    std::list<Unit *> enemyList;
    std::vector<FieldObject *> collectPoints;
    std::vector<Bullet *> bullets;
    for (auto i:level.getStaticObjectsByName("collect")) {
        collectPoints.push_back(
                new FieldObject(level, i.name, i.imagePath, i.rect.left, i.rect.top, i.rect.width, i.rect.height));
    }
    for (auto i:level.getObjectsByType("hero")) {
        Hero *hero = new Hero(level, std::stof(i.properties["precision"]), i.name, i.imagePath, i.rect.left, i.rect.top,
                              i.rect.width, i.rect.height, mapView);
        heroList.push_back(hero);

    }
    for (auto i:level.getObjectsByType("enemy")) {
        if (i.subType == "forager_enemy") {
            ForagerEnemy *fenemy = new ForagerEnemy(level, collectPoints, i.name, i.imagePath, i.rect.left, i.rect.top,
                                                    i.rect.width, i.rect.height, mapView);
            enemyList.push_back(fenemy);
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
        float enemyTime = getSumOfTimePoints(enemyList);
        float heroTime = getSumOfTimePoints(heroList);
        float time = clock.getElapsedTime().asMilliseconds(); //дать прошедшее время в микросекундах
        if (time > 15) {
            clock.restart();
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
                b->update(time);
                if (!b->isAlive) {
                    it = heroList.erase(it);
                    delete b;
                }
                if (heroTime >= 0) {
                    b->toSelect(pos, event);
                    if (b->isSelect) {
                        inventBar.getUnit(b);
                    }
                    if (b->isMove) {
                        b->doStep(time);
                        mapView.getplayercoordforview(b->x, b->y);

                    }
                    /*for (auto item: itemsList) {
                        if (b->getRect().intersects(item->getRect()) && item->state == Item::STATE::onMap) {
                            if (Keyboard::isKeyPressed(Keyboard::T)) {
                                b->takeItem(item);
                            }
                        }

                    }*/
                    if (b->isAlive) {
                        if (itemsClock.getElapsedTime().asMilliseconds() > 200) {
                            for (auto item : itemsList) {
                                if (b->getRect().intersects(item->getRect()) && item->state == Item::STATE::onMap) {
                                    if (Keyboard::isKeyPressed(sf::Keyboard::T)) {
                                        if (dynamic_cast<Weapon *>(item) != nullptr) {
                                            b->takeWeapon(dynamic_cast<Weapon *>(item));
                                        } else
                                            b->takeItem(item);
                                        itemsClock.restart();
                                    }
                                }
                            }
                        }
                    }
                }
            }
            for (auto it = enemyList.begin(); it != enemyList.end(); it++) {
                Unit *b = *it;
                b->update(time);
                if (!b->isAlive) {
                    it = enemyList.erase(it);
                    delete b;
                }
                if (enemyTime >= 0 && heroTime <= 0) {
                    b->toSelect(pos, event);
                    if (b->isSelect && dynamic_cast<ItemCollector *>(b) != nullptr) {
                        inventBar.getUnit(dynamic_cast<ItemCollector *>(b));
                    }
                    if (b->isMove) {
                        b->doStep(time);
                        mapView.getplayercoordforview(b->x, b->y);
                    }
                    /*for (auto item: itemsList) {
                        if (dynamic_cast<ItemCollector *>(b) != nullptr) {
                            if (b->getRect().intersects(item->getRect()) && item->state == Item::STATE::onMap) {
                                if (Keyboard::isKeyPressed(Keyboard::T)) {
                                    dynamic_cast<ItemCollector *>(b)->takeItem(item);
                                }
                            }
                        }

                    }*/
                    if (itemsClock.getElapsedTime().asMilliseconds() > 200) {
                        for (auto item : itemsList) {
                            if (dynamic_cast<ItemCollector *>(b) != nullptr) {
                                if (b->getRect().intersects(item->getRect()) && item->state == Item::STATE::onMap) {
                                    if (Keyboard::isKeyPressed(sf::Keyboard::T)) {
                                        dynamic_cast<ItemCollector *>(b)->takeItem(item);
                                        itemsClock.restart();
                                    }
                                }
                            }
                            if (dynamic_cast<Shooter *>(b) != nullptr && dynamic_cast<Weapon *>(item) != nullptr) {
                                if (b->getRect().intersects(item->getRect()) && item->state == Item::STATE::onMap) {
                                    if (Keyboard::isKeyPressed(sf::Keyboard::T)) {
                                        dynamic_cast<Shooter *>(b)->takeWeapon(dynamic_cast<Weapon *>(item));
                                        itemsClock.restart();
                                    }
                                }
                            }
                            item->update(time);
                        }
                    }
                    if (attackClock.getElapsedTime().asMilliseconds() > 100) {
                        for (auto hero:heroList) {
                            if (dynamic_cast<WildEnemy *>(b) != nullptr) {
                                if (b->getRect().intersects(hero->getRect())) {
                                    if (Keyboard::isKeyPressed(sf::Keyboard::A)) {
                                        dynamic_cast<WildEnemy *>(b)->makeDamage(hero);
                                        hero->update(time);
                                        attackClock.restart();
                                    }
                                }

                            }
                        }

                    }
                }
            }
            if (enemyTime <= 0 && heroTime <= 0) {
                updateSquadTime(heroList);
                updateSquadTime(enemyList);
            }
        }
        mapView.viewMap(time);
        mapView.changeView();
        //inventBar.getUnit(heroList.front());
        window.setView(mapView.view);
        window.clear();
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
                if (hero->getWeapon() != nullptr) {
                    hero->getWeapon()->sprite.setPosition(hero->x + 3, hero->y + 1);
                    hero->getWeapon()->draw(window);
                }
            }
        }
        for (auto enemy: enemyList) {
            if (enemy->isAlive) {
                enemy->draw(window);
                if (dynamic_cast<Shooter *>(enemy) != nullptr &&
                    dynamic_cast<Shooter *>(enemy)->getWeapon() != nullptr) {
                    dynamic_cast<Shooter *>(enemy)->getWeapon()->sprite.setPosition(enemy->x + 3, enemy->y + 1);
                    dynamic_cast<Shooter *>(enemy)->getWeapon()->draw(window);
                }
            }
        }
        for (auto b:bullets) {
            if (b->isAlive) {
                b->doShoot(time);
                b->draw(window);
                b->update(time);
            }
        }
        inventBar.draw(window);
        window.display();
    }
}
