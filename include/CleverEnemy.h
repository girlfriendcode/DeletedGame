//
// Created by mi on 22.11.2020.
//

#ifndef GAME_CLEVERENEMY_H
#define GAME_CLEVERENEMY_H

#include "Shooter.h"
#include "Carrier.h"
#include "Weapon.h"
/**
 * Класс разумного существа
 */
class CleverEnemy : public Carrier, public Shooter {
public:
    CleverEnemy(Level &level, std::vector<FieldObject *> points, float precision, std::string &name,
                std::string &fileName, float x, float y, float w, float h, myView &view);


};

#endif //GAME_CLEVERENEMY_H
