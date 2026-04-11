#include "raylib.h"
#include "globals.h"
#include "map.h"

/*
    - 0 = floor (laufbar)
    - 1 = Wall (zerstörbar)
    - 2 = Bedrock (nicht zerstörbar)
    - 3 = Bomb
*/

MapData currentMap;

void InitMap() {
    
    
    switch (Curent_map_Size) {
        case map_Small:
            width = 13;
            height = 6;
            break;
        case map_Medium:
            width = 29;
            height = 14;
            break;
        case map_Big:
            width = 39;
            height = 21;
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
                currentMap.data[y][x] = TILE_BEDROCK;
            }
            else {
                if (GetRandomValue(0, 99) < 50) {
                    currentMap.data[y][x] = TILE_WALL;
                } else {
                    currentMap.data[y][x] = TILE_FLOOR;
                }
            }
        }
    }
    currentMap.data[1][1] = TILE_FLOOR;                           // Spieler 1 Start
    currentMap.data[height-2][width-2] = TILE_FLOOR; 
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
            else {
                DrawRectangle(x * blockSize, y * blockSize, blockSize, blockSize, GREEN);
            }
            // TILE_FLOOR wird nicht gezeichnet (transparent/weiß)
        }
    }
}