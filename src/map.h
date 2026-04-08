#pragma once
#include "raylib.h"
#include <vector>

struct MapData {
    std::vector<std::vector<int>> data;
    int width;
    int height;
};

extern MapData currentMap;

void InitMap();
void DrawMap();