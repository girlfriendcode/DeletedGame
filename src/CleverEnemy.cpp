//
// Created by valeria on 02.12.2020.
//

#include "../include/CleverEnemy.h"

CleverEnemy::CleverEnemy(Level &level, std::vector<FieldObject *> points, float precision, std::string &name,
                         std::string &fileName, float x, float y, float w, float h, myView &view)
        : Shooter(level, precision, name, fileName, x, y, w, h, view),
          Carrier(level, points, name, fileName, x, y, w, h, view), Unit(level, name, fileName, x, y, w, h, view) {

}

