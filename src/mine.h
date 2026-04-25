#pragma once
#include <iostream>
#include <vector>
#include "map.h"
#include "mine.h"
class Player;
struct minen {
    int posx;
    int posy;
    bool visible;
    bool active;
};

extern std::vector<minen> mineList;


bool setmine(int x, int y, Player& player);
void DrawMine();
void dropMine(int x, int y);

bool isplayerOnMine(const Player& player, const minen& mine);
void explodemine(Player& player1, Player& player2);