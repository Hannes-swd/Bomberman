#include "raylib.h"
#include "globals.h"
#include "map.h"

MapData currentMap;

void InitMap() {
    int width, height;
    
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
    
    // Vector mit Größe height, jeder Eintrag ein vector<int> mit Größe width
    currentMap.data.assign(height, std::vector<int>(width, 0));
    currentMap.width = width;
    currentMap.height = height;
    
    // Map befüllen
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (y == 0 || y == height-1 || x == 0 || x == width-1) {
                currentMap.data[y][x] = 2; // Wand
            }
            else if (x % 2 == 0 && y % 2 == 0) {
                currentMap.data[y][x] = 1; // Block
            }
            else {
                currentMap.data[y][x] = 0; // Leer
            }
        }
    }
}

void DrawMap() {
    int blockSize = 32;
    
    for (int y = 0; y < currentMap.height; y++) {
        for (int x = 0; x < currentMap.width; x++) {
            if (currentMap.data[y][x] == 1) {
                DrawRectangle(x * blockSize, y * blockSize, blockSize, blockSize, BROWN);
            }
            else if (currentMap.data[y][x] == 2) {
                DrawRectangle(x * blockSize, y * blockSize, blockSize, blockSize, DARKGRAY);
            }
        }
    }
}