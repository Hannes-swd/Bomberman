#pragma once
#include <iostream>
#include <vector>
#include "map.h"
#include "mine.h"

struct minen {
    int posx;
    int posy;
    bool visible;
};

extern std::vector<minen> mineList;


void setmine(int x, int y);
void Drawmiome();