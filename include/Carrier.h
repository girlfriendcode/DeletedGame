//
// Created by valeria on 28.11.2020.
//

#ifndef DELETEDGAME_CARRIER_H
#define DELETEDGAME_CARRIER_H

#include "main.h"
#include "Unit.h"
/**
 * Класс знающего точки складированя
 */
class Carrier : virtual public Unit {
protected:

    std::vector<FieldObject *> collectPoints;
public:
    Carrier(Level &level, std::vector<FieldObject *> points, std::string &name, std::string &fileName, float x, float y,
            float w, float h, myView &view, std::map<std::string, std::string> properties);

    std::tuple<float, float> getNearestPoint();//в зависимости от расположения игрока сейчас
    //предусмотреть, чтобы в режиме врагов были видны точки складирования
    std::vector<FieldObject *> getCollectPoints() const { return collectPoints; };
};

#endif //DELETEDGAME_CARRIER_H
