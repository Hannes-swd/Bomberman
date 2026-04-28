#pragma once
#include "player.h"
#include <vector>

struct SmokeBomb   // geändert
{
    int posx;
    int posy;
    Player* owner;
};

extern std::vector<SmokeBomb> smokeBombList;   // geändert

void placeSmokeBomb(int x, int y, Player* owner);
void drawsmokeBomb();
void explodeSmokeBomb(Player* owner);