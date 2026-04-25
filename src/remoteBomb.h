#pragma once
#include "player.h"

struct remoteBomb
{
    int posx;
    int posy;
    Player* owner;
};
extern std::vector<remoteBomb> remoteBombList;

void placeremoteBomb(int x, int y,Player* owner);
void drawremoteBomb();