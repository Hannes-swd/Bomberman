#pragma once
#include <iostream>
#include <vector>
#include "map.h"

// define functions & struct
void placeBomb(int x, int y, int explosionRange);
void drawBomb();
void deleteBomb();
void bombExplode(int posX, int posY, int explosionRange);

struct Bomb {
    int posX;
    int posY;
    double spawnTime;
    bool hasExploded;
    int explosionRange;  // Individuelle Explosionsgröße für jede Bombe
};

// Neue Variable für Explosionsdauer
struct Explosion {
    int posX;
    int posY;
    double startTime;
};

// define list - nur Deklarationen, keine Definitionen!
extern std::vector<Bomb> BombList;
extern std::vector<Explosion> ExplosionList;