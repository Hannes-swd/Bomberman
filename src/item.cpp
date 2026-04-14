#include "bomb.h"
#include <raylib.h>
#include <iostream>
#include "textures.h"
#include "map.h"
#include <algorithm>
#include "item.h"
std::vector<ItemsOnGround> ItemsOngroundList;

void DrawItems() {
    for (const auto& ItemsOnGround : ItemsOngroundList) {
        float scale = 32.0f / textures["BombUpgrade"].width;
        float drawX = (float)ItemsOnGround.posx - (textures["BombUpgrade"].width * scale) / 2.0f;
        float drawY = (float)ItemsOnGround.posy - (textures["BombUpgrade"].height * scale) / 2.0f;
        DrawTextureEx(textures["BombUpgrade"], { drawX + 16, drawY + 16 }, 0, scale, WHITE);
    }
}
void placeItem(Items item, int posx, int posy) {
    ItemsOnGround newItem;
    newItem.item = item;
    newItem.posx = posx * 32;
    newItem.posy = posy * 32;
    ItemsOngroundList.push_back(newItem);
}