
#include "../include/Inventory.h"
#include "../include/Hero.h"

Inventory::Inventory() {
}

void Inventory::draw(RenderWindow &window) {
    Vector2f center = window.getView().getCenter();
    Vector2f size = window.getView().getSize();

    //отрисовка бара с аптечками и патронами
    float itemsBarOriginX = center.x - size.x / 2 + 10;
    float itemsBarOriginY = center.y - 90;
    itemsBar.setPosition(itemsBarOriginX, itemsBarOriginY);
    itemsBar.setSize({60, 300});
    itemsBar.setOutlineColor(outLineColor);
    itemsBar.setFillColor(fillColor);
    itemsBar.setOutlineThickness(2);
    window.draw(itemsBar);

    //отрисовка бара оружия
    float weaponsBarOriginX = center.x + size.x / 2 - 60;
    float weaponsBarOriginY = center.y - 90;
    weaponsBar.setPosition(weaponsBarOriginX, weaponsBarOriginY);
    weaponsBar.setSize({60, 300});
    weaponsBar.setOutlineColor(outLineColor);
    weaponsBar.setFillColor(fillColor);
    weaponsBar.setOutlineThickness(2);
    window.draw(weaponsBar);
    float itemOriginY = itemsBarOriginY + 10;
    if (!itemCollector->inventory.empty()) {
        int index = 0;
        for (int i = 0; i < itemCollector->inventory.getSize(); i++) {
            if (dynamic_cast<Weapon *>(itemCollector->inventory[i]) == nullptr) {
                itemCollector->inventory[i]->sprite.setScale(0.9, 0.9);
                itemCollector->inventory[i]->x = itemsBarOriginX + 10;
                itemCollector->inventory[i]->y = itemsBarOriginY + 10;
                itemCollector->inventory[i]->sprite.setPosition(itemCollector->inventory[i]->x,
                                                                itemCollector->inventory[i]->y);
                itemsBarOriginY += 50;
            } else {
                itemCollector->inventory[i]->sprite.setScale(0.9, 0.9);
                itemCollector->inventory[i]->x = weaponsBarOriginX + 10;
                itemCollector->inventory[i]->y = weaponsBarOriginY + 10;
                itemCollector->inventory[i]->sprite.setPosition(itemCollector->inventory[i]->x,
                                                                itemCollector->inventory[i]->y);
                weaponsBarOriginY += 50;
            }

            window.draw(itemCollector->inventory[i]->sprite);


            if (dynamic_cast<Hero *>(itemCollector) != nullptr) {
                if (dynamic_cast<Hero *>(itemCollector)->currItem == index) {
                    RectangleShape usingItem;
                    usingItem.setPosition(itemCollector->inventory[i]->x - 5, itemCollector->inventory[i]->y);
                    usingItem.setSize({50, 50});
                    usingItem.setOutlineColor(Color::Blue);
                    usingItem.setOutlineThickness(2);
                    usingItem.setFillColor(Color::Transparent);
                    window.draw(usingItem);
                }
                index++;
            }
        }
    }

}



