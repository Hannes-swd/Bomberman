#include <vector>
#include <algorithm>
#include "raylib.h"
#include "smokeBomb.h"
#include "textures.h"
#include "player.h"
#include "map.h"     
#include "bomb.h" 

std::vector<SmokeBomb> smokeBombList;   // Typ geändert

void placeSmokeBomb(int x, int y, Player* owner) {
    SmokeBomb newsmokeBomb;            // Typ geändert

    int GridX = (int)(x / 32);
    int GridY = (int)(y / 32);
    if (currentMap.data[GridY][GridX] != TILE_FLOOR) return;

    newsmokeBomb.posx = GridX * 32;
    newsmokeBomb.posy = GridY * 32;
    newsmokeBomb.owner = owner;

    smokeBombList.push_back(newsmokeBomb);
}

void drawsmokeBomb() {
    for (const auto& bomb : smokeBombList) {
        float scale = 26.0f / textures["smokebomb"].width;
        float drawX = (float)bomb.posx - (textures["smokebomb"].width * scale) / 2.0f;
        float drawY = (float)bomb.posy - (textures["smokebomb"].height * scale) / 2.0f;
        DrawTextureEx(textures["smokebomb"], { drawX + 16, drawY + 16 }, 0, scale, WHITE);
    }
}

void explodeSmokeBomb(Player* owner) {
    for (auto& bomb : smokeBombList) {
        if (bomb.owner == owner) {
            bombExplode(bomb.posx, bomb.posy, owner->getBombRange(), owner);
        }
    }
    
    smokeBombList.erase(
        std::remove_if(smokeBombList.begin(), smokeBombList.end(),
            [owner](const SmokeBomb& b) {
                return b.owner == owner;
            }),
        smokeBombList.end()
    );
}