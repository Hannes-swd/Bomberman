// imports
#pragma once
#include <iostream>
#include <vector>

#include "map.h"
#include "player.h"



// include player class
class Player;



// define functions
void placeBomb(int x, int y, int explosionRange, Player* owner);
void drawBomb();
void destroyWall(int gridX, int gridY, Player* owner); 
void bombExplode(int posX, int posY, int explosionRange, Player* owner);
void deleteBomb();
bool isPlayerInExplosion(double playerX, double playerY);



// create struct for bomb elements
struct Bomb {
    int posX;
    int posY;
    double spawnTime;
    bool hasExploded;
    int explosionRange;  
    Player* owner;
};



// create struct for bomb explosion time
struct Explosion {
    int posX;
    int posY;
    double startTime;
};



// declare lists
extern std::vector<Bomb> BombList;
extern std::vector<Explosion> ExplosionList;