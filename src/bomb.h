#pragma once
#include <iostream>
#include <vector>

// define functions & struct
void placeBomb(int x, int y);
void drawBomb();
void deleteBomb();

struct Bomb {
    int posX;
    int posY;
    double spawnTime;
};

// define list
extern std::vector<Bomb> BombList;