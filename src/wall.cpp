#include "map.h"

void drawWall(double posX, double posY){
    int gridX = (int)(posX / 32) * 32;
    int gridY = (int)(posY / 32) * 32;

    if (gridX >= 0 && gridX < currentMap.width && gridY >= 0 && gridY < currentMap.height) {
        if (currentMap.data[gridY][gridX] == TILE_FLOOR) {
            // replace with wall tile
            currentMap.data[gridY][gridX] = TILE_WALL;
        }
    }
}