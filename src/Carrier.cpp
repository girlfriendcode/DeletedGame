//
// Created by valeria on 28.11.2020.
//
#include "../include/Carrier.h"
#include <cmath>

Carrier::Carrier(Level &level, std::vector<FieldObject *> points, std::string &name, std::string &fileName, float x,
                 float y, float w, float h, myView &view, std::map<std::string, std::string> properties) : Unit(level,
                                                                                                                name,
                                                                                                                fileName,
                                                                                                                x, y, w,
                                                                                                                h, view,
                                                                                                                properties) {
    collectPoints.assign(points.begin(), points.end());
}

std::tuple<float, float> Carrier::getNearestPoint() {
    float minDistance = 100.0;
    float MinX = 0;
    float MinY = 0;
    auto iter = collectPoints.begin();
    while (iter != collectPoints.end()) {
        float X = (*iter)->getX();
        float Y = (*iter)->getY();
        if (minDistance >= std::sqrt(X * X + Y * Y)) {
            minDistance = std::sqrt(X * X + Y * Y);
            MinX = X;
            MinY = Y;
        }
        ++iter;
    }
    return std::make_tuple(MinX, MinY);
}
