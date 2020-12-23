#pragma once

#include "../include/Hero.h"
#include "../include/Level.h"
#include "../include/WildEnemy.h"
#include "../include/BulletCase.h"
#include "../include/MedChest.h"
#include "../include/ForagerEnemy.h"
#include "../include/CleverEnemy.h"
#include "../include/Weapon.h"
#include "gtest/gtest.h"

TEST(Hero, Properties) {
    Level level;
    level.loadStaticObjects("../res/map.tmx");
    level.loadDynamicObjects("../res/objects.xml");
    myView myView;
    std::vector<MapObject> heroList = level.getObjectsByType("hero");
    Hero hero = Hero(level, std::stof(heroList[1].properties["precision"]), heroList[1].name, heroList[1].imagePath,
                     heroList[1].rect.left, heroList[1].rect.top,
                     heroList[1].rect.width, heroList[1].rect.height, myView);

    ASSERT_FLOAT_EQ(hero.x, 240);
    ASSERT_FLOAT_EQ(hero.basicStats["maxTime"], 5000);
    ASSERT_FLOAT_EQ(hero.basicStats["timeStep"], 20);
    ASSERT_STRCASEEQ("hero", heroList[1].name.c_str());
}

TEST(WildEnemy, Properties) {
    Level level;
    level.loadStaticObjects("../res/map.tmx");
    level.loadDynamicObjects("../res/objects.xml");
    myView myView;
    std::vector<MapObject> wildEnemyList = level.getObjectsByName("wild_enemy");
    WildEnemy wildEnemy = WildEnemy(level, std::stof(wildEnemyList[0].properties["precision"]),
                                    std::stof(wildEnemyList[0].properties["damage"]), wildEnemyList[0].name,
                                    wildEnemyList[0].imagePath,
                                    wildEnemyList[0].rect.left, wildEnemyList[0].rect.top, wildEnemyList[0].rect.width,
                                    wildEnemyList[0].rect.height, myView);
    ASSERT_FLOAT_EQ(wildEnemy.basicStats["radius"], 100);
    ASSERT_FLOAT_EQ(wildEnemy.y, 130);
    ASSERT_FLOAT_EQ(wildEnemy.getDamage(), 15);
}

TEST(ForagerEnemy, Properties) {
    Level level;
    level.loadStaticObjects("../res/map.tmx");
    level.loadDynamicObjects("../res/objects.xml");
    myView myView;
    std::vector<MapObject> foragerEnemyList = level.getObjectsByName("forager_enemy");
    std::vector<FieldObject *> collectPoints;
    ForagerEnemy foragerEnemy = ForagerEnemy(level, collectPoints, foragerEnemyList[0].name,
                                             foragerEnemyList[0].imagePath, foragerEnemyList[0].rect.left,
                                             foragerEnemyList[0].rect.top,
                                             foragerEnemyList[0].rect.width, foragerEnemyList[0].rect.height, myView);
    ASSERT_FLOAT_EQ(foragerEnemy.basicStats["radius"], 100);
    ASSERT_FLOAT_EQ(foragerEnemy.y, 576);
    ASSERT_FLOAT_EQ(foragerEnemy.basicStats["maxHealth"], 500);
}

TEST(CleverEnemy, Properties) {
    Level level;
    level.loadStaticObjects("../res/map.tmx");
    level.loadDynamicObjects("../res/objects.xml");
    myView myView;
    std::vector<MapObject> cleverEnemyList = level.getObjectsByName("clever_enemy");
    std::vector<FieldObject *> collectPoints;
    CleverEnemy cleverEnemy = CleverEnemy(level, collectPoints, std::stof(cleverEnemyList[0].properties["precision"]),
                                          cleverEnemyList[0].name, cleverEnemyList[0].imagePath,
                                          cleverEnemyList[0].rect.left, cleverEnemyList[0].rect.top,
                                          cleverEnemyList[0].rect.width, cleverEnemyList[0].rect.height, myView);
    ASSERT_FLOAT_EQ(cleverEnemy.basicStats["radius"], 100);
    ASSERT_FLOAT_EQ(cleverEnemy.y, 600);
    ASSERT_FLOAT_EQ(cleverEnemy.getPrecision(), 0.6);
}

TEST(MedChest, Actions) {
    Level level;
    level.loadStaticObjects("../res/map.tmx");
    level.loadDynamicObjects("../res/objects.xml");
    myView myView;
    std::vector<MapObject> medChestList = level.getObjectsByName("med");
    MedChest med = MedChest(level, std::stof(medChestList[0].properties["time_rec"]),
                            std::stof(medChestList[0].properties["hp"]),
                            std::stoi(medChestList[2].properties["weight"]), medChestList[0].name,
                            medChestList[0].imagePath,
                            medChestList[0].rect.left, medChestList[0].rect.top, medChestList[0].rect.width,
                            medChestList[0].rect.height);
    ASSERT_FLOAT_EQ(med.gettimeRec(), 15);
    ASSERT_FLOAT_EQ(med.getWeight(), 3);
    ASSERT_FLOAT_EQ(med.getHp(), 20);
    std::vector<MapObject> heroList = level.getObjectsByType("hero");
    Hero hero = Hero(level, std::stof(heroList[1].properties["precision"]), heroList[1].name, heroList[1].imagePath,
                     heroList[1].rect.left, heroList[1].rect.top,
                     heroList[1].rect.width, heroList[1].rect.height, myView);
    hero.basicStats["health"] -= 20;
    hero.useMedecine(&med);
    ASSERT_EQ(hero.basicStats["health"], 500);
}

TEST(Weapon, Actions) {
    Level level;
    level.loadStaticObjects("../res/map.tmx");
    level.loadDynamicObjects("../res/objects.xml");
    myView myView;
    std::vector<MapObject> weaponList = level.getObjectsByName("weapon_auto");
    Weapon weapon = Weapon(level, std::stof(weaponList[0].properties["damage"]),
                           std::stof(weaponList[0].properties["time_shoot"]),
                           std::stof(weaponList[0].properties["time_charge"]),
                           std::stoi(weaponList[0].properties["bulletType"]),
                           std::stoi(weaponList[0].properties["maxbullets"]),
                           std::stoi(weaponList[0].properties["weight"]),
                           weaponList[0].name, weaponList[0].imagePath,
                           weaponList[0].rect.left, weaponList[0].rect.top, weaponList[0].rect.width,
                           weaponList[0].rect.height);
    ASSERT_EQ(weapon.gettimeShoot(), 5);
    ASSERT_EQ(weapon.getmaxBullets(), 15);
    ASSERT_EQ(weapon.getWeight(), 5);
    std::vector<FieldObject *> collectPoints;
    std::vector<MapObject> cleverEnemyList = level.getObjectsByName("clever_enemy");
    CleverEnemy cleverEnemy = CleverEnemy(level, collectPoints, std::stof(cleverEnemyList[0].properties["precision"]),
                                          cleverEnemyList[0].name, cleverEnemyList[0].imagePath,
                                          cleverEnemyList[0].rect.left, cleverEnemyList[0].rect.top,
                                          cleverEnemyList[0].rect.width, cleverEnemyList[0].rect.height, myView);
    cleverEnemy.takeWeapon(&weapon);
    ASSERT_FLOAT_EQ(cleverEnemy.getWeapon()->getW_Damage(), 20);
    cleverEnemy.getWeapon()->setBullets(5);
    ASSERT_EQ(weapon.getBullets(), 5);
    CleverEnemy cleverEnemy1 = CleverEnemy(level, collectPoints, std::stof(cleverEnemyList[1].properties["precision"]),
                                           cleverEnemyList[1].name, cleverEnemyList[1].imagePath,
                                           cleverEnemyList[1].rect.left, cleverEnemyList[1].rect.top,
                                           cleverEnemyList[1].rect.width, cleverEnemyList[1].rect.height, myView);
    ASSERT_TRUE(cleverEnemy1.getWeapon() == nullptr);
}

TEST(BulletCase, Actions) {
    Level level;
    level.loadStaticObjects("../res/map.tmx");
    level.loadDynamicObjects("../res/objects.xml");
    myView myView;
    std::vector<MapObject> weaponList = level.getObjectsByName("weapon_riffle");
    Weapon weapon = Weapon(level, std::stof(weaponList[0].properties["damage"]),
                           std::stof(weaponList[0].properties["time_shoot"]),
                           std::stof(weaponList[0].properties["time_charge"]),
                           std::stoi(weaponList[0].properties["bulletType"]),
                           std::stoi(weaponList[0].properties["maxbullets"]),
                           std::stoi(weaponList[0].properties["weight"]),
                           weaponList[0].name, weaponList[0].imagePath,
                           weaponList[0].rect.left, weaponList[0].rect.top, weaponList[0].rect.width,
                           weaponList[0].rect.height);
    std::vector<MapObject> caseList = level.getObjectsByName("riffle_c");
    BulletCase bulletCase = BulletCase(level, std::stoi(caseList[1].properties["maxbullets"]),
                                       std::stoi(caseList[1].properties["bulletType"]),
                                       std::stoi(caseList[1].properties["weight"]), caseList[1].name,
                                       caseList[1].imagePath,
                                       caseList[1].rect.left, caseList[1].rect.top, caseList[1].rect.width,
                                       caseList[1].rect.height);
    ASSERT_EQ(bulletCase.bulletType, 3);
    ASSERT_EQ(bulletCase.getWeight(), 5);
    std::vector<MapObject> heroList = level.getObjectsByType("hero");
    Hero hero = Hero(level, std::stof(heroList[1].properties["precision"]), heroList[1].name, heroList[1].imagePath,
                     heroList[1].rect.left, heroList[1].rect.top,
                     heroList[1].rect.width, heroList[1].rect.height, myView);
    hero.takeWeapon(&weapon);
    hero.getWeapon()->setBullets(0);
    hero.takeItem(&bulletCase);
    hero.recharge(&bulletCase);
    ASSERT_EQ(0, bulletCase.getBullets());
    ASSERT_EQ(10, hero.getWeapon()->getBullets());
}

TEST(Attack, Methods) {
    Level level;
    level.loadStaticObjects("../res/map.tmx");
    level.loadDynamicObjects("../res/objects.xml");
    myView myView;
    std::vector<MapObject> heroList = level.getObjectsByType("hero");
    Hero hero = Hero(level, std::stof(heroList[1].properties["precision"]), heroList[1].name, heroList[1].imagePath,
                     heroList[1].rect.left, heroList[1].rect.top,
                     heroList[1].rect.width, heroList[1].rect.height, myView);
    std::vector<MapObject> weaponList = level.getObjectsByName("weapon_riffle");
    Weapon weapon = Weapon(level, std::stof(weaponList[0].properties["damage"]),
                           std::stof(weaponList[0].properties["time_shoot"]),
                           std::stof(weaponList[0].properties["time_charge"]),
                           std::stoi(weaponList[0].properties["bulletType"]),
                           std::stoi(weaponList[0].properties["maxbullets"]),
                           std::stoi(weaponList[0].properties["weight"]),
                           weaponList[0].name, weaponList[0].imagePath,
                           weaponList[0].rect.left, weaponList[0].rect.top, weaponList[0].rect.width,
                           weaponList[0].rect.height);
    std::vector<MapObject> wildEnemyList = level.getObjectsByName("wild_enemy");
    WildEnemy wildEnemy = WildEnemy(level, std::stof(wildEnemyList[0].properties["precision"]),
                                    std::stof(wildEnemyList[0].properties["damage"]), wildEnemyList[0].name,
                                    wildEnemyList[0].imagePath,
                                    wildEnemyList[0].rect.left, wildEnemyList[0].rect.top, wildEnemyList[0].rect.width,
                                    wildEnemyList[0].rect.height, myView);
    hero.takeWeapon(&weapon);
    wildEnemy.makeDamage(&hero);
    sf::Event event;
    Vector2f pos;
    ASSERT_FLOAT_EQ(hero.basicStats["health"], 485);
    hero.makeShoot(&wildEnemy, pos, event);
    ASSERT_FLOAT_EQ(wildEnemy.basicStats["health"], 470);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

