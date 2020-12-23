//
// Created by valeria on 02.12.2020.
//

#include "../include/ForagerEnemy.h"

ForagerEnemy::ForagerEnemy(Level &level, std::vector<FieldObject *> points, std::string &name, std::string &fileName,
                           float x,
                           float y, float w, float h, myView &view) : Carrier(level, points, name, fileName, x, y, w, h,
                                                                              view),
                                                                      Unit(level, name, fileName, x, y, w, h, view),
                                                                      ItemCollector(level, name, fileName, x, y, w, h,
                                                                                    view) {
}

