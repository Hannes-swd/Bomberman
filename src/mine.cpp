#include <iostream>
#include <vector>
#include "raylib.h"
#include "map.h"
#include "mine.h"
#include "textures.h"
#include "item.h"
#include "player.h"

std::vector<minen> mineList;

bool setmine(int x, int y, Player& player) {
    
    int GridX = (int)(x / 32);
    int GridY = (int)(y / 32);
    if (currentMap.data[GridY][GridX] != TILE_FLOOR) return false;
    
    minen newmine;
    newmine.posx = GridX * 32;
    newmine.posy = GridY * 32;
    newmine.visible = true;
    newmine.active = false;
    mineList.push_back(newmine);
    return true;
}

void DrawMine() {
    for (const auto& mine : mineList) {
        float scale = 26.0f / textures["mine"].width;
        float drawX = (float)mine.posx - (textures["mine"].width * scale) / 2.0f;
        float drawY = (float)mine.posy - (textures["mine"].height * scale) / 2.0f;
        if (mine.visible)
            DrawTextureEx(textures["mine"], { drawX + 16, drawY + 16 }, 0, scale, WHITE);
    }
}

void dropMine(int x, int y) {
    int GridX = (int)(x / 32);
    int GridY = (int)(y / 32);
    placeItem(MineItem, GridX, GridY);
}

bool isplayerOnMine(const Player& player, const minen& mine) {
    double px = player.getPositionX();
    double py = player.getPositionY();
    return (px >= mine.posx && px < mine.posx + 32 &&
            py >= mine.posy && py < mine.posy + 32);
}

void explodemine(Player& player1, Player& player2) {
    for (size_t i = 0; i < mineList.size(); ) {
        minen& mine = mineList[i];
        bool player1OnMine = isplayerOnMine(player1, mine);
        bool player2OnMine = isplayerOnMine(player2, mine);
        bool anyPlayerOnMine = player1OnMine || player2OnMine;

        if (anyPlayerOnMine) {
            if (mine.active) {
                if (player1OnMine) player1.takeDamage(2);
                if (player2OnMine) player2.takeDamage(2);
                mineList.erase(mineList.begin() + i);
            } else {
                i++;
            }
        } else {
            if (!mine.active) {
                mine.active = true;
                mine.visible = false;
                std::cout << "Mine aktiviert!" << std::endl;
            }
            i++;
        }
    }
}