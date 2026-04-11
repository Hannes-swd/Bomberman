#include "raylib.h"
#include "globals.h"
#include "map.h"

/*
    - 0 = floor (laufbar)
    - 1 = Wall (zerstörbar)
    - 2 = Bedrock (nicht zerstörbar)
*/

MapData currentMap;

void InitMap() {
    
    
    switch (Curent_map_Size) {
        case map_Small:
            width = 14;
            height = 7;
            break;
        case map_Medium:
            width = 30;
            height = 15;
            break;
        case map_Big:
            width = 40;
            height = 20;
            break;
    }
    
    // Vector mit Größe height, jeder Eintrag ein vector<Tiles> mit Größe width
    currentMap.data.assign(height, std::vector<Tiles>(width, TILE_FLOOR));
    currentMap.width = width;
    currentMap.height = height;
    
    // Map befüllen
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (y == 0 || y == height-1 || x == 0 || x == width-1) {
                currentMap.data[y][x] = TILE_BEDROCK;
            }
            else if (x % 2 == 0 && y % 2 == 0) {
                currentMap.data[y][x] = TILE_WALL;
            }
            else {
                currentMap.data[y][x] = TILE_FLOOR;
            }
        }
    }
}

void DrawMap() {
    int blockSize = 32;
    
    for (int y = 0; y < currentMap.height; y++) {
        for (int x = 0; x < currentMap.width; x++) {
            if (currentMap.data[y][x] == TILE_WALL) {
                DrawRectangle(x * blockSize, y * blockSize, blockSize, blockSize, BROWN);
            }
            else if (currentMap.data[y][x] == TILE_BEDROCK) {
                DrawRectangle(x * blockSize, y * blockSize, blockSize, blockSize, DARKGRAY);
            }
            // TILE_FLOOR wird nicht gezeichnet (transparent/weiß)
        }
    }
}