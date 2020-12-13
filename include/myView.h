//
// Created by valeria on 07.12.2020.
//

#ifndef DELETEDGAME_MYVIEW_H
#define DELETEDGAME_MYVIEW_H

#include "main.h"

using namespace sf;

class myView {
public:
    sf::View view;

    void getplayercoordforview(int x, int y);

    void viewMap(float time);

    void changeView();
};

#endif //DELETEDGAME_MYVIEW_H
