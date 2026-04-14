// imports
#include <raylib.h>
#include <iostream>
#include <algorithm>

#include "bomb.h"
#include "textures.h"
#include "map.h"
#include "item.h"
#include <algorithm>



// define global variables
std::vector<Bomb> BombList;
std::vector<Explosion> ExplosionList;



// add bomb element to bomblist
void placeBomb(int x, int y, int explosionRange) {
    // create new bomb element
    Bomb newBomb;

    // set X & Y in Grid
    int GridX = (int)(x / 32);
    int GridY = (int)(y / 32);

    // return if not on floor element
    if (currentMap.data[GridY][GridX] != TILE_FLOOR) return;

    // position bomb in grid
    newBomb.posX = GridX * 32;
    newBomb.posY = GridY * 32;

    // set bomb properties
    newBomb.explosionRange = explosionRange; 
    newBomb.spawnTime = GetTime();
    newBomb.hasExploded = false;

    // add bomb to bomblist
    BombList.push_back(newBomb);
}



// function to draw bomb & explosion in field
void drawBomb() {
    // draw bomb for every element in bomblist
    for (const auto& Bomb : BombList) {
        // if not exploded
        if (!Bomb.hasExploded) {
            // scale and position
            float scale = 32.0f / textures["bomb"].width;
            float drawX = (float)Bomb.posX - (textures["bomb"].width * scale) / 2.0f;
            float drawY = (float)Bomb.posY - (textures["bomb"].height * scale) / 2.0f;

            // draw as texture
            DrawTextureEx(textures["bomb"], { drawX + 16, drawY + 16 }, 0, scale, WHITE);
        }
    }
    
    // draw explotion for every element in explosionlist
    double now = GetTime();
    for (const auto& exp : ExplosionList) {
        // if time to explode bomb
        if ((now - exp.startTime) < 0.3) {
            // draw explotion with border
            DrawRectangle(exp.posX, exp.posY, 32, 32, RED);
            DrawRectangleLines(exp.posX, exp.posY, 32, 32, ORANGE);
        }
    }
}



// function to destroy wall tile
void destroyWall(int gridX, int gridY) {
    if (gridX >= 0 && gridX < currentMap.width && gridY >= 0 && gridY < currentMap.height) {
        if (currentMap.data[gridY][gridX] == TILE_WALL) {
            // replace with floor tile
            currentMap.data[gridY][gridX] = TILE_FLOOR;

            //upgrade
            placeItem(BombUpgrade, gridX, gridY);
        }
    }
}



// function to calculate explosion range
void addExplosionInDirection(int startGridX, int startGridY, int dx, int dy, int range) {
    for (int i = 1; i <= range; i++) {
        // get start position
        int checkX = startGridX + (dx * i);
        int checkY = startGridY + (dy * i);
        
        // check if not in grid
        if (checkX < 0 || checkX >= currentMap.width || checkY < 0 || checkY >= currentMap.height) {
            break;
        }
        
        // do not destroy bedrock
        if (currentMap.data[checkY][checkX] == TILE_BEDROCK) {
            break;
        }
        
        // create new explotion element
        Explosion newExp;

        // set explotion element in grid
        newExp.posX = checkX * 32;
        newExp.posY = checkY * 32;

        // set properties to explosion element
        newExp.startTime = GetTime();
        ExplosionList.push_back(newExp);
        
        // destroy wall if in range
        if (currentMap.data[checkY][checkX] == TILE_WALL) {
            destroyWall(checkX, checkY);
            break;
        }
    }
}



// function for bomb explosion
void bombExplode(int posX, int posY, int explosionRange) {
    // get position in grid
    int gridX = posX / 32;
    int gridY = posY / 32;
    
    // create new explotion element
    Explosion centerExp;

    // set explotion element in grid
    centerExp.posX = posX;
    centerExp.posY = posY;

    // set properties to explosion element
    centerExp.startTime = GetTime();
    ExplosionList.push_back(centerExp);
    
    // explode in all directions
    addExplosionInDirection(gridX, gridY, 1, 0, explosionRange);
    addExplosionInDirection(gridX, gridY, -1, 0, explosionRange);
    addExplosionInDirection(gridX, gridY, 0, 1, explosionRange);
    addExplosionInDirection(gridX, gridY, 0, -1, explosionRange);
}



// function to erase bomb
void deleteBomb() {
    // get current time
    double now = GetTime();
    
    // remove explotions that are older then 3 secs
    ExplosionList.erase(
        std::remove_if(ExplosionList.begin(), ExplosionList.end(),
            [now](const Explosion& e) {
                return (now - e.startTime) >= 0.3;
            }),
        ExplosionList.end()
    );
    
    // explode bombs
    for (auto& bomb : BombList) {
        if (!bomb.hasExploded && (now - bomb.spawnTime) >= 3.0) {
            bombExplode(bomb.posX, bomb.posY, bomb.explosionRange);
            bomb.hasExploded = true;
        }
    }
    
    // remove exploded bombs
    BombList.erase(
        std::remove_if(BombList.begin(), BombList.end(),
            [](const Bomb& b) {
                return b.hasExploded;
            }),
        BombList.end()
    );
}



// function to add damage to players in explostion range
bool isPlayerInExplosion(double playerX, double playerY) {
    // get current time
    double now = GetTime();

    // check if in explotion range
    for (const auto& exp : ExplosionList) {
        // if not in time
        if ((now - exp.startTime) >= 0.5) continue; 
        
        // return true if in range
        if (playerX >= exp.posX && playerX < exp.posX + 32 &&
            playerY >= exp.posY && playerY < exp.posY + 32) {
            return true;
        }
    }

    // return false if not in range
    return false;
}