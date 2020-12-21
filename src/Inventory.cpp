
#include "../include/Inventory.h"

Inventory::Inventory() {
    if (!font.loadFromFile("../res/fonts/GameFont.ttf"))
        std::cout << "Font cannot be downloaded";

}

void Inventory::draw(RenderWindow &window) {
    Vector2f center = window.getView().getCenter();
    Vector2f size = window.getView().getSize();
    //отрисовка бара с аптечками и патронами
    float itemsBarOriginX = center.x - size.x / 2 + 10;
    std::cout << "window x y" << abs(center.x - size.x) << std::endl;
    std::cout << "window size" << size.x << std::endl;
    float itemsBarOriginY = center.y - 200;
    itemsBar.setPosition(itemsBarOriginX, itemsBarOriginY);
    itemsBar.setSize({50, 300});
    itemsBar.setOutlineColor(outLineColor);
    itemsBar.setFillColor(fillColor);
    itemsBar.setOutlineThickness(2);
    window.draw(itemsBar);
    //отрисовка бара оружия
    float weaponsBarOriginX = center.x + size.x / 2 - 60;
    float weaponsBarOriginY = center.y - 200;
    weaponsBar.setPosition(weaponsBarOriginX, weaponsBarOriginY);
    weaponsBar.setSize({50, 300});
    weaponsBar.setOutlineColor(outLineColor);
    weaponsBar.setFillColor(fillColor);
    weaponsBar.setOutlineThickness(2);
    window.draw(weaponsBar);
    float itemOriginY = itemsBarOriginY + 10;
    if (!itemCollector->inventory.empty()) {
        for (int i = 0; i < itemCollector->inventory.getSize(); i++) {
            if (dynamic_cast<Weapon *>(itemCollector->inventory[i]) == nullptr) {
                itemCollector->inventory[i]->sprite.setScale(0.7, 0.7);
                itemCollector->inventory[i]->x = itemsBarOriginX + 10;
                itemCollector->inventory[i]->y = itemsBarOriginY + 10;
                itemCollector->inventory[i]->sprite.setPosition(itemCollector->inventory[i]->x,
                                                                itemCollector->inventory[i]->y);
            } else {
                itemCollector->inventory[i]->sprite.setScale(0.7, 0.7);
                itemCollector->inventory[i]->x = weaponsBarOriginX + 10;
                itemCollector->inventory[i]->y = weaponsBarOriginY + 10;
                itemCollector->inventory[i]->sprite.setPosition(itemCollector->inventory[i]->x,
                                                                itemCollector->inventory[i]->y);
            }
            window.draw(itemCollector->inventory[i]->sprite);
            itemsBarOriginY += 30;
            weaponsBarOriginY += 30;
        }
    }

}



