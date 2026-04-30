#pragma once
#include "player.h"
#include <vector>

struct SmokeBomb
{
    int posx;
    int posy;
    Player* owner;
    double explosionTime;
};

struct SmokeCloud
{
    int posx;
    int posy;
    double startTime;
    double duration;
};

extern std::vector<SmokeBomb> smokeBombList;
extern std::vector<SmokeCloud> smokeCloudList;  

void placeSmokeBomb(int x, int y, Player* owner);
void drawSmokeBomb();
void drawSmokeClouds();              
void updateSmokeClouds();
void updateAllSmokes();