#include "raylib.h"
#include "globals.h"
#include "map.h"

#define SMALL_WIDTH 14
#define SMALL_HEIGHT 7
#define MEDIUM_WIDTH 30
#define MEDIUM_HEIGHT 15
#define BIG_WIDTH 40
#define BIG_HEIGHT 20

int smallMapData[SMALL_HEIGHT][SMALL_WIDTH];
int mediumMapData[MEDIUM_HEIGHT][MEDIUM_WIDTH];
int bigMapData[BIG_HEIGHT][BIG_WIDTH];

void InitMap() {
    // Small Map
    for (int y = 0; y < SMALL_HEIGHT; y++) {
        for (int x = 0; x < SMALL_WIDTH; x++) {
            if (y == 0 || y == SMALL_HEIGHT-1 || x == 0 || x == SMALL_WIDTH-1) {
                smallMapData[y][x] = 2;
            }
            else if (x % 2 == 0 && y % 2 == 0) {
                smallMapData[y][x] = 1;
            }
            else {
                smallMapData[y][x] = 0;
            }
        }
    }
    
    // Medium Map
    for (int y = 0; y < MEDIUM_HEIGHT; y++) {
        for (int x = 0; x < MEDIUM_WIDTH; x++) {
            if (y == 0 || y == MEDIUM_HEIGHT-1 || x == 0 || x == MEDIUM_WIDTH-1) {
                mediumMapData[y][x] = 2;
            }
            else if (x % 2 == 0 && y % 2 == 0) {
                mediumMapData[y][x] = 1;
            }
            else {
                mediumMapData[y][x] = 0;
            }
        }
    }
    
    // Big Map
    for (int y = 0; y < BIG_HEIGHT; y++) {
        for (int x = 0; x < BIG_WIDTH; x++) {
            if (y == 0 || y == BIG_HEIGHT-1 || x == 0 || x == BIG_WIDTH-1) {
                bigMapData[y][x] = 2;
            }
            else if (x % 2 == 0 && y % 2 == 0) {
                bigMapData[y][x] = 1;
            }
            else {
                bigMapData[y][x] = 0;
            }
        }
    }
}

void DrawMap() {
    int blockSize = 32;
    
    if (Curent_map_Size == map_Small) {
        for (int y = 0; y < SMALL_HEIGHT; y++) {
            for (int x = 0; x < SMALL_WIDTH; x++) {
                if (smallMapData[y][x] == 1) {
                    DrawRectangle(x * blockSize, y * blockSize, blockSize, blockSize, BROWN);
                }
                else if (smallMapData[y][x] == 2) {
                    DrawRectangle(x * blockSize, y * blockSize, blockSize, blockSize, DARKGRAY);
                }
            }
        }
    }
    else if (Curent_map_Size == map_Medium) {
        for (int y = 0; y < MEDIUM_HEIGHT; y++) {
            for (int x = 0; x < MEDIUM_WIDTH; x++) {
                if (mediumMapData[y][x] == 1) {
                    DrawRectangle(x * blockSize, y * blockSize, blockSize, blockSize, BROWN);
                }
                else if (mediumMapData[y][x] == 2) {
                    DrawRectangle(x * blockSize, y * blockSize, blockSize, blockSize, DARKGRAY);
                }
            }
        }
    }
    else if (Curent_map_Size == map_Big) {
        for (int y = 0; y < BIG_HEIGHT; y++) {
            for (int x = 0; x < BIG_WIDTH; x++) {
                if (bigMapData[y][x] == 1) {
                    DrawRectangle(x * blockSize, y * blockSize, blockSize, blockSize, BROWN);
                }
                else if (bigMapData[y][x] == 2) {
                    DrawRectangle(x * blockSize, y * blockSize, blockSize, blockSize, DARKGRAY);
                }
            }
        }
    }
}