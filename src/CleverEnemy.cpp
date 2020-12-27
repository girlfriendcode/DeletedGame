//
// Created by valeria on 02.12.2020.
//

#include "../include/CleverEnemy.h"

CleverEnemy::CleverEnemy(Level &level, std::vector<FieldObject *> points, float precision, std::string &name,
                         std::string &fileName, float x, float y, float w, float h, myView &view,
                         std::map<std::string, std::string> properties)
        : Shooter(level, precision, name, fileName, x, y, w, h, view, properties),
          Carrier(level, points, name, fileName, x, y, w, h, view, properties),
          Unit(level, name, fileName, x, y, w, h, view, properties) {

}

