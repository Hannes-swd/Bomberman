#pragma once
#include "raylib.h"
#include <string>
#include <vector>

// Enum zuerst definieren
enum Tiles {
    TILE_FLOOR,
    TILE_WALL,
    TILE_BEDROCK
};

struct MapData {
    std::vector<std::vector<Tiles>> data;
    int width;
    int height;
};

extern MapData currentMap;
extern std::string textDisplay;
extern Color textColor;

void InitMap();
void DrawMap();
void DrawDeathScreen(std::string color);