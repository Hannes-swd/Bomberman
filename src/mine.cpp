#include <iostream>
#include <vector>
#include "raylib.h"
#include "map.h"
#include "mine.h"
#include "textures.h"

std::vector<minen> mineList;

void setmine(int x ,int y) {
    minen newmine;
    int GridX = (int)(x / 32);
    int GridY = (int)(y / 32);
    if (currentMap.data[GridY][GridX] != TILE_FLOOR) return;
    newmine.posx = GridX * 32;
    newmine.posy = GridY * 32;
    newmine.visible = true;
    mineList.push_back(newmine);
}

void Drawmiome() {
    for (const auto& mine : mineList) {
        float scale = 26.0f / textures["mine"].width;
        float drawX = (float)mine.posx - (textures["mine"].width * scale) / 2.0f;
        float drawY = (float)mine.posy - (textures["mine"].height * scale) / 2.0f;
        DrawTextureEx(textures["mine"], { drawX + 16, drawY + 16 }, 0, scale, WHITE);
    }
}