#pragma once
#include <iostream>
#include <vector>

// define functions & struct
void placeBomb(int x, int y);
void drawBomb();

struct Bomb {
    int posX;
    int posY;
};

// define list
extern std::vector<Bomb> BombList;