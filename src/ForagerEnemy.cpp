//
// Created by valeria on 02.12.2020.
//

#include "../include/ForagerEnemy.h"

ForagerEnemy::ForagerEnemy(Level &level, std::vector<FieldObject *> points, std::string &name, std::string &fileName,
                           float x,
                           float y, float w, float h, myView &view, std::map<std::string, std::string> properties)
        : Carrier(level, points, name, fileName, x, y, w, h,
                  view, properties),
          Unit(level, name, fileName, x, y, w, h, view, properties),
          ItemCollector(level, name, fileName, x, y, w, h,
                        view, properties) {
}

