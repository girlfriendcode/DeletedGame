
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
    Clock clock, itemsClock, attackClock, shooter1Clock, shooter2Clock, inventoryClock;
    std::list<Item *> itemsList;
    std::list<Hero *> heroList;
    Inventory inventBar;
    sf::RectangleShape shape;
    std::list<Inventory *> inventList;
    std::list<Unit *> enemyList;
    //std::list<Shooter*> shootersList;
    std::vector<FieldObject *> collectPoints;
    std::vector<Bullet *> bullets;
    for (auto i:level.getStaticObjectsByName("collect")) {
        collectPoints.push_back(
                new FieldObject(level, i.name, i.imagePath, i.rect.left, i.rect.top, i.rect.width, i.rect.height));
    }
    for (auto i:level.getObjectsByType("hero")) {
        Hero *hero = new Hero(level, std::stof(i.properties["precision"]), i.name, i.imagePath, i.rect.left, i.rect.top,
                              i.rect.width, i.rect.height, mapView, i.properties);
        heroList.push_back(hero);
        //shootersList.push_back(hero);

    }
    for (auto i:level.getObjectsByType("enemy")) {
        if (i.subType == "forager_enemy") {
            ForagerEnemy *fenemy = new ForagerEnemy(level, collectPoints, i.name, i.imagePath, i.rect.left, i.rect.top,
                                                    i.rect.width, i.rect.height, mapView, i.properties);
            enemyList.push_back(fenemy);
        }
        if (i.subType == "clever_enemy") {
            CleverEnemy *cleverEnemy = new CleverEnemy(level, collectPoints, std::stof(i.properties["precision"]),
                                                       i.name,
                                                       i.imagePath, i.rect.left, i.rect.top, i.rect.width,
                                                       i.rect.height,
                                                       mapView, i.properties);
            enemyList.push_back(cleverEnemy);
            //shootersList.push_back(cleverEnemy);
        }
        if (i.subType == "wild_enemy") {
            enemyList.push_back((Unit *) new WildEnemy(level, std::stof(i.properties["precision"]),
                                                       std::stof(i.properties["damage"]), i.name, i.imagePath,
                                                       i.rect.left, i.rect.top, i.rect.width, i.rect.height, mapView,
                                                       i.properties));
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

            //std::cout << pixelPos.x
            //       << "\n";//смотрим на координату Х позиции курсора в консоли (она не будет больше ширины окна)
            //std::cout << pos.x << "\n";//смотрим на Х,которая преобразовалась в мировые координаты
            Unit *selectedUnit = nullptr;
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::KeyPressed) {
                    //обрабатываем в цикле событий, иначе потом будет литься куча пуль
                }
            }

            for (auto it = heroList.begin(); it != heroList.end(); it++) {

                Hero *b = *it;
                b->update(time);
                if (!b->isAlive) {
                    b->throwItem(b->x + 5, b->y + 5);
                    it = heroList.erase(it);
                    //delete b;
                }

                if (heroTime > 0) {

                    b->toSelect(pos, event);
                    if (b->isSelect) {
                        inventBar.getUnit(b);

                    }

                    if (b->isMove) {
                        b->doStep(time);
                        mapView.getplayercoordforview(b->x, b->y);

                    }
                    if (b->isAlive) {
                        if (itemsClock.getElapsedTime().asMilliseconds() > 200) {
                            for (auto item : itemsList) {
                                if (b->getRect().intersects(item->getRect()) && item->state == Item::STATE::onMap) {
                                    if (Keyboard::isKeyPressed(Keyboard::T)) {
                                        if (dynamic_cast<Weapon *>(item) != nullptr) {
                                            b->takeWeapon(dynamic_cast<Weapon *>(item));
                                        } else
                                            b->takeItem(item);
                                        itemsClock.restart();
                                    }
                                }
                            }
                        }
                        if (inventoryClock.getElapsedTime().asMilliseconds() > 200 && b->isSelect) {
                            if (Keyboard::isKeyPressed(Keyboard::W)) {
                                inventoryClock.restart();
                                if (b->currItem == b->inventory.getSize() - 1) {
                                    b->currItem = 0;
                                    break;
                                } else {
                                    b->currItem++;
                                    break;
                                }
                                std::cout << "currItem" << b->currItem << std::endl;
                            }
                            if (Keyboard::isKeyPressed(Keyboard::U)) {
                                inventoryClock.restart();
                                if (!b->inventory.empty()) {
                                    if (dynamic_cast<MedChest *>(b->inventory[b->currItem])) {
                                        if (b->basicStats["health"] != b->basicStats["maxHealth"]) {
                                            std::cout << "health before" << b->basicStats["health"] << std::endl;
                                            b->useMedecine(dynamic_cast<MedChest *>(b->inventory[b->currItem]));
                                            b->inventory.erase(b->currItem);
                                        }
                                    }
                                    if (dynamic_cast<BulletCase *>(b->inventory[b->currItem]) &&
                                        dynamic_cast<BulletCase *>(b->inventory[b->currItem])->bulletType ==
                                        b->getWeapon()->bulletType) {
                                        if (b->getWeapon()->getBullets() != b->getWeapon()->getmaxBullets()) {
                                            b->recharge(dynamic_cast<BulletCase *>(b->inventory[b->currItem]));
                                            if (dynamic_cast<BulletCase *>(b->inventory[b->currItem])->getBullets() <=
                                                0) {
                                                b->inventory.erase(b->currItem);
                                            }
                                        }
                                    }
                                    if (dynamic_cast<Weapon *>(b->inventory[b->currItem])) {
                                        b->activateWeapon(dynamic_cast<Weapon *>(b->inventory[b->currItem]));
                                    }
                                }
                            }
                            if (Keyboard::isKeyPressed(Keyboard::D)) {
                                inventoryClock.restart();
                                if (dynamic_cast<Weapon *>(b->inventory[b->currItem]))
                                    b->throwWeapon(dynamic_cast<Weapon *>(b->inventory[b->currItem]));
                                else
                                    b->throwItem(b->inventory[b->currItem]);
                                if (b->currItem == b->inventory.getSize() - 1) {
                                    b->currItem = 0;
                                    break;
                                } else {
                                    b->currItem++;
                                    break;
                                }
                            }
                        }
                        if (shooter1Clock.getElapsedTime().asMilliseconds() > 400) {
                            if ((Keyboard::isKeyPressed(Keyboard::Space)) && b->isSelect) {
                                if (b->getWeapon() != nullptr && b->getWeapon()->getBullets() > 0) {
                                    Bullet *bull = new Bullet(level, b->x, b->y, pos.x,
                                                              pos.y);//cоздаю пулю - пока нет ружья, стреляем из точки (100,100)
                                    bull->toPoint(pos);
                                    bullets.push_back(bull);//кладем в вектор
                                    b->makeShoot();
                                    b->isShooting = true;
                                    shooter1Clock.restart();
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
                    if (dynamic_cast<Shooter *>(b) != nullptr)
                        dynamic_cast<Shooter *>(b)->throwWeapon();
                    if (dynamic_cast<ItemCollector *>(b) != nullptr) {
                        dynamic_cast<ItemCollector *>(b)->throwItem(b->x + 5, b->y + 5);
                    }
                }
                if (enemyTime > 0 && heroTime <= 0) {
                    b->toSelect(pos, event);
                    if (b->isSelect && dynamic_cast<ItemCollector *>(b) != nullptr) {
                        inventBar.getUnit(dynamic_cast<ItemCollector *>(b));
                    }
                    if (b->isMove) {
                        b->doStep(time);
                        mapView.getplayercoordforview(b->x, b->y);
                    }
                    //для разброса вещей
                    float itx = b->x;
                    float ity = b->y;
                    if (itemsClock.getElapsedTime().asMilliseconds() > 350) {
                        for (auto item : itemsList) {
                            if (dynamic_cast<ItemCollector *>(b) != nullptr) {
                                if (b->getRect().intersects(item->getRect()) && item->state == Item::STATE::onMap) {
                                    if (Keyboard::isKeyPressed(Keyboard::T)) {
                                        dynamic_cast<ItemCollector *>(b)->takeItem(item);
                                        itemsClock.restart();
                                    }
                                }
                                if (Keyboard::isKeyPressed(sf::Keyboard::D) && b->isSelect) {
                                    itemsClock.restart();
                                    dynamic_cast<ItemCollector *>(b)->throwItem(itx, ity);
                                    itx += 30;
                                    ity += 30;
                                }

                            }
                            if (dynamic_cast<Shooter *>(b) != nullptr && dynamic_cast<Weapon *>(item) != nullptr) {
                                if (b->getRect().intersects(item->getRect()) && item->state == Item::STATE::onMap) {
                                    if (Keyboard::isKeyPressed(Keyboard::T)) {
                                        dynamic_cast<Shooter *>(b)->takeWeapon(dynamic_cast<Weapon *>(item));
                                        itemsClock.restart();
                                    }
                                }
                                if (Keyboard::isKeyPressed(sf::Keyboard::D) && b->isSelect) {
                                    itemsClock.restart();
                                    dynamic_cast<Shooter *>(b)->throwWeapon();
                                }

                            }
                            item->update(time);
                        }
                    }
                    if (attackClock.getElapsedTime().asMilliseconds() > 100) {
                        for (auto hero:heroList) {
                            if (dynamic_cast<WildEnemy *>(b) != nullptr) {
                                if (b->getRect().intersects(hero->getRect())) {
                                    if (Keyboard::isKeyPressed(Keyboard::A)) {
                                        dynamic_cast<WildEnemy *>(b)->makeDamage(hero);
                                        hero->update(time);
                                        attackClock.restart();
                                    }
                                }

                            }
                        }
                    }
                    if (shooter2Clock.getElapsedTime().asMilliseconds() > 400) {
                        if (dynamic_cast<Shooter *>(b) != nullptr) {
                            if ((Keyboard::isKeyPressed(Keyboard::Space)) && b->isSelect) {
                                if (dynamic_cast<Shooter *>(b)->getWeapon() != nullptr &&
                                    dynamic_cast<Shooter *>(b)->getWeapon()->getBullets() > 0) {
                                    Bullet *bull = new Bullet(level, b->x, b->y, pos.x,
                                                              pos.y);//cоздаю пулю - пока нет ружья, стреляем из точки (100,100)
                                    bull->toPoint(pos);
                                    bullets.push_back(bull);//кладем в вектор
                                    dynamic_cast<Shooter *>(b)->makeShoot();
                                    dynamic_cast<Shooter *>(b)->isShooting = true;
                                    shooter2Clock.restart();
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
                if (hero->isSelect) {
                    inventBar.draw(window);
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
                if (dynamic_cast<ItemCollector *>(enemy) != nullptr && enemy->isSelect) {
                    inventBar.draw(window);
                }
            }
        }
        for (auto b:bullets) {
            if (b->isAlive) {
                b->doShoot(time);
                b->draw(window);
                b->update(time);
                for (auto hero:heroList) {
                    if (hero->isShooting && hero->isAlive) {
                        for (auto enemy:enemyList) {
                            if (b->getRect().intersects(enemy->getRect())) {
                                hero->attack(enemy);
                                enemy->update(time);
                                hero->isShooting = false;
                            }
                        }

                    }
                }
                for (auto enemy:enemyList) {
                    if (dynamic_cast<Shooter *>(enemy)) {
                        if (dynamic_cast<Shooter *>(enemy)->isShooting && enemy->isAlive) {
                            for (auto hero:heroList) {
                                if (b->getRect().intersects(hero->getRect())) {
                                    dynamic_cast<Shooter *>(enemy)->attack(hero);
                                    hero->update(time);
                                    dynamic_cast<Shooter *>(enemy)->isShooting = false;
                                }
                            }

                        }
                    }
                }
            }

        }
        window.display();
        if (getSumOfHealth(enemyList) <= 0) {
            std::cout << "HEROES WON!" << std::endl;
            window.close();
        }
        if (getSumOfHealth(heroList) <= 0) {
            std::cout << "ENEMIES WON!" << std::endl;
            window.close();
        }
    }
}

float DeletedGame::getSumOfHealth(std::list<Unit *> units) {
    float sum = 0;
    for (auto unit:units) {
        if (unit->isAlive) {
            sum += unit->basicStats["health"];
        }
    }
    return sum;
}

float DeletedGame::getSumOfHealth(std::list<Hero *> heroes) {
    float sum = 0;
    for (auto unit:heroes) {
        if (unit->isAlive) {
            sum += unit->basicStats["health"];
        }
    }
    return sum;
}
