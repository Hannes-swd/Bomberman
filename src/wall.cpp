#include "map.h"
#include "player.h"

class Player;

void drawWall(double posX, double posY, Player& p1, Player& p2){
    int gridX = (int)(posX / 32);
    int gridY = (int)(posY / 32);

    int p1x = (int)(p1.getPositionX() / 32);
    int p1y = (int)(p1.getPositionY() / 32);
    int p2x = (int)(p2.getPositionX() / 32);
    int p2y = (int)(p2.getPositionY() / 32);

    if (gridX == p1x && gridY == p1y) return;
    if (gridX == p2x && gridY == p2y) return;

    if (gridX >= 0 && gridX < currentMap.width && gridY >= 0 && gridY < currentMap.height) {
        if (currentMap.data[gridY][gridX] == TILE_FLOOR) {
            // replace with wall tile
            currentMap.data[gridY][gridX] = TILE_WALL;
        }
    }
}