//
// Created by valeria on 02.12.2020.
//

#ifndef DELETEDGAME_LAYER_H
#define DELETEDGAME_LAYER_H

#include <iostream>
#include "main.h"

// слой тайлов
class Layer {
public:
    int opacity;
    std::vector<sf::Sprite> tiles;

    Layer layer();
};

#endif //DELETEDGAME_LAYER_H
