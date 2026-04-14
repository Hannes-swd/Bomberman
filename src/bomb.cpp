#include "bomb.h"
#include <raylib.h>
#include <iostream>
#include "textures.h"
#include "map.h"
#include <algorithm>

// Definitionen der globalen Variablen
std::vector<Bomb> BombList;
std::vector<Explosion> ExplosionList;

// function to add bomb element
void placeBomb(int x, int y, int explosionRange) {
    Bomb newBomb;
    int GridX = (int)(x / 32);
    int GridY = (int)(y / 32);

    if (currentMap.data[GridY][GridX] != TILE_FLOOR) return;

    newBomb.posX = GridX * 32;
    newBomb.posY = GridY * 32;
    newBomb.spawnTime = GetTime();
    newBomb.hasExploded = false;
    newBomb.explosionRange = explosionRange;  // Individuelle Reichweite setzen

    BombList.push_back(newBomb);
}

// function to draw bombs
void drawBomb() {
    for (const auto& Bomb : BombList) {
        if (!Bomb.hasExploded) {
            float scale = 32.0f / textures["bomb"].width;
            float drawX = (float)Bomb.posX - (textures["bomb"].width * scale) / 2.0f;
            float drawY = (float)Bomb.posY - (textures["bomb"].height * scale) / 2.0f;
            DrawTextureEx(textures["bomb"], { drawX + 16, drawY + 16 }, 0, scale, WHITE);
        }
    }
    
    // Explosionen zeichnen
    double now = GetTime();
    for (const auto& exp : ExplosionList) {
        if ((now - exp.startTime) < 0.5) {
            DrawRectangle(exp.posX, exp.posY, 32, 32, RED);
            DrawRectangleLines(exp.posX, exp.posY, 32, 32, ORANGE);
        }
    }
}

// Funktion um ein Tile zu zerstören
void destroyWall(int gridX, int gridY) {
    if (gridX >= 0 && gridX < currentMap.width && gridY >= 0 && gridY < currentMap.height) {
        if (currentMap.data[gridY][gridX] == TILE_WALL) {
            currentMap.data[gridY][gridX] = TILE_FLOOR;
        }
    }
}

// Funktion um Explosionsradius zu berechnen
void addExplosionInDirection(int startGridX, int startGridY, int dx, int dy, int range) {
    for (int i = 1; i <= range; i++) {
        int checkX = startGridX + (dx * i);
        int checkY = startGridY + (dy * i);
        
        if (checkX < 0 || checkX >= currentMap.width || checkY < 0 || checkY >= currentMap.height) {
            break;
        }
        
        if (currentMap.data[checkY][checkX] == TILE_BEDROCK) {
            break;
        }
        
        Explosion newExp;
        newExp.posX = checkX * 32;
        newExp.posY = checkY * 32;
        newExp.startTime = GetTime();
        ExplosionList.push_back(newExp);
        
        if (currentMap.data[checkY][checkX] == TILE_WALL) {
            destroyWall(checkX, checkY);
            break;
        }
    }
}

// function for bomb explosion
void bombExplode(int posX, int posY, int explosionRange) {
    int gridX = posX / 32;
    int gridY = posY / 32;
    
    // Zentrum der Explosion
    Explosion centerExp;
    centerExp.posX = posX;
    centerExp.posY = posY;
    centerExp.startTime = GetTime();
    ExplosionList.push_back(centerExp);
    
    // In alle 4 Richtungen mit individueller Reichweite explodieren
    addExplosionInDirection(gridX, gridY, 1, 0, explosionRange);
    addExplosionInDirection(gridX, gridY, -1, 0, explosionRange);
    addExplosionInDirection(gridX, gridY, 0, 1, explosionRange);
    addExplosionInDirection(gridX, gridY, 0, -1, explosionRange);
    
    std::cout << "Bomb exploded at (" << posX << ", " << posY << ") with range " << explosionRange << "!" << std::endl;
}

// function to erase bomb
void deleteBomb() {
    double now = GetTime();
    
    // Explosionen entfernen, die älter als 0.5 Sekunden sind
    ExplosionList.erase(
        std::remove_if(ExplosionList.begin(), ExplosionList.end(),
            [now](const Explosion& e) {
                return (now - e.startTime) >= 0.5;
            }),
        ExplosionList.end()
    );
    
    // Bomben explodieren lassen
    for (auto& bomb : BombList) {
        if (!bomb.hasExploded && (now - bomb.spawnTime) >= 5.0) {
            bombExplode(bomb.posX, bomb.posY, bomb.explosionRange);
            bomb.hasExploded = true;
        }
    }
    
    // Explodierte Bomben entfernen
    BombList.erase(
        std::remove_if(BombList.begin(), BombList.end(),
            [](const Bomb& b) {
                return b.hasExploded;
            }),
        BombList.end()
    );
}

bool isPlayerInExplosion(double playerX, double playerY) {
    double now = GetTime();
    for (const auto& exp : ExplosionList) {
        if ((now - exp.startTime) >= 0.5) continue; 
        
        
        if (playerX >= exp.posX && playerX < exp.posX + 32 &&
            playerY >= exp.posY && playerY < exp.posY + 32) {
            return true;
        }
    }
    return false;
}