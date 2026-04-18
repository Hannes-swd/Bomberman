#pragma once
#include <iostream>
#include <vector>
#include "map.h"
#include "player.h"

class Player;

// define functions & struct
void placeBomb(int x, int y, int explosionRange, Player* owner);
void drawBomb();
void deleteBomb();
void destroyWall(int gridX, int gridY, Player* owner); 
void bombExplode(int posX, int posY, int explosionRange, Player* owner);

struct Bomb {
    int posX;
    int posY;
    double spawnTime;
    bool hasExploded;
    int explosionRange;  // Individuelle Explosionsgröße für jede Bombe
    Player* owner;
};

// Neue Variable für Explosionsdauer
struct Explosion {
    int posX;
    int posY;
    double startTime;
};

bool isPlayerInExplosion(double playerX, double playerY);

// define list - nur Deklarationen, keine Definitionen!
extern std::vector<Bomb> BombList;
extern std::vector<Explosion> ExplosionList;