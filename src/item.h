#pragma once
#include <vector>
#include "player.h"


void DrawItems();
enum Items {
    BombUpgrade,
    Bombcount,
};
struct ItemsOnGround  {
    Items item;
    int posx;
    int posy;
};
extern std::vector<ItemsOnGround> ItemsOngroundList;
void placeItem(Items item, int posx, int posy);

void colecktItem(Player& player1, Player& player2);