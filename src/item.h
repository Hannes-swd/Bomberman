#pragma once
#include <vector>
#include "player.h"


void DrawItems();
enum Items { // items on ground
    BombUpgrade,
    Bombcount,
    MineItem,

    //remotebomb
    remotebombItem,
    remotebombdetonatorItem,

    HealingPotionItem,
    GhostItem,

    smokeBombItem,
};
struct ItemsOnGround  {
    Items item;
    int posx;
    int posy;
};
extern std::vector<ItemsOnGround> ItemsOngroundList;
void placeItem(Items item, int posx, int posy);

void colecktItem(Player& player1, Player& player2);