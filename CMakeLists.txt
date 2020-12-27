cmake_minimum_required(VERSION 3.17)
project(DeletedGame)

set(CMAKE_CXX_STANDARD 17)
enable_testing()
set(TINY_SOURCES "include/TinyXML/tinyxml.h"
        "include/TinyXML/tinystr.h"
        "include/TinyXML/tinystr.cpp"
        "include/TinyXML/tinyxml.cpp"
        "include/TinyXML/tinyxmlparser.cpp"
        "include/TinyXML/tinyxmlerror.cpp" include/myView.h src/myView.cpp include/Bullet.h src/Bullet.cpp include/MyContainer.h include/Inventory.h src/Inventory.cpp)
SET(GAME_SOURCES
        include/Level.h
        include/Item.h
        include/Unit.h
        include/WildEnemy.h
        include/ForagerEnemy.h
        include/CleverEnemy.h
        include/FieldObject.h
        include/MedChest.h
        include/Weapon.h
        include/Hero.h
        src/Unit.cpp
        src/FieldObject.cpp
        src/Level.cpp
        src/Hero.cpp
        include/main.h
        src/DeletedGame.cpp
        include/DeletedGame.h
        include/BulletCase.h
        include/ItemCollector.h
        include/MyContainer.h
        include/Inventory.h
        include/Bullet.h
        include/Shooter.h
        include/Carrier.h
        src/Shooter.cpp
        src/Carrier.cpp
        src/ItemCollector.cpp
        src/Item.cpp
        src/BulletCase.cpp
        src/MedChest.cpp
        src/WildEnemy.cpp
        src/CleverEnemy.cpp
        src/ForagerEnemy.cpp
        src/Weapon.cpp
        include/MapObject.h
        src/MapObject.cpp
        include/Layer.h
        src/Layer.cpp)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(DeletedGame
        src/main.cpp
        ${TINY_SOURCES}
        ${GAME_SOURCES})

add_executable(runUnitTests gtest/gtest.cpp
        ${GAME_SOURCES}
        ${TINY_SOURCES})
set(gtest_disable_pthreads on)
target_link_libraries(runUnitTests gtest gtest_main)

target_link_libraries(runUnitTests sfml-graphics sfml-audio)
target_link_libraries(DeletedGame sfml-graphics sfml-audio)
