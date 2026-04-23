#include "bomb.h"
#include <raylib.h>
#include <iostream>
#include "textures.h"
#include "map.h"
#include <algorithm>
#include "item.h"
std::vector<ItemsOnGround> ItemsOngroundList;

void DrawItems() {
    for (const auto& item : ItemsOngroundList) {
        float scale;
        Texture2D tex;
        
        if (item.item == BombUpgrade) {
            tex = textures["BombUpgrade"];
            scale = 26.0f / tex.width;
        } else if (item.item == Bombcount) {
            tex = textures["BpombCount"];
            scale = 26.0f / tex.width;
        } else if (item.item == MineItem) {
            tex = textures["mine"];
            scale = 26.0f / tex.width;
        }
        
        float drawX = (float)item.posx - (tex.width * scale) / 2.0f;
        float drawY = (float)item.posy - (tex.height * scale) / 2.0f;
        DrawTextureEx(tex, { drawX + 16, drawY + 16 }, 0, scale, WHITE);
    }
}

void placeItem(Items item, int posx, int posy) {
    ItemsOnGround newItem;
    newItem.item = item;
    newItem.posx = posx * 32;
    newItem.posy = posy * 32;
    ItemsOngroundList.push_back(newItem);
}


void colecktItem(Player& player1, Player& player2) {
    for (size_t i = 0; i < ItemsOngroundList.size(); i++) {
        ItemsOnGround& item = ItemsOngroundList[i];
        //player1
        if (player1.getPositionX() >= item.posx && 
            player1.getPositionX() < item.posx + 32 &&
            player1.getPositionY() >= item.posy && 
            player1.getPositionY() < item.posy + 32) {
            
            switch (item.item) {
                case BombUpgrade:
                    player1.addBombRange();
                    break;
                case Bombcount:
                    player1.addBombCounte();
                    break;
                case MineItem:
                    player1.addItem(mine, 1);
                    break;
            }
            
            ItemsOngroundList.erase(ItemsOngroundList.begin() + i);
            i--; 
        }
        //player2
        else if (player2.getPositionX() >= item.posx && 
                 player2.getPositionX() < item.posx + 32 &&
                 player2.getPositionY() >= item.posy && 
                 player2.getPositionY() < item.posy + 32) {
            
            switch (item.item) {
                case BombUpgrade:
                    player2.addBombRange();
                    break;
                case Bombcount:
                    player2.addBombCounte();
                    break;
                case MineItem:
                    player2.addItem(mine, 1);
                    break;
            }
            
            ItemsOngroundList.erase(ItemsOngroundList.begin() + i);
            i--;
        }
    }
}