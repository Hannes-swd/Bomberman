#include <vector>
#include <algorithm>

#include "raylib.h"
#include "remoteBomb.h"
#include "textures.h"
#include "player.h"

std::vector<remoteBomb> remoteBombList;

void placeremoteBomb(int x, int y,Player* owner) {
    remoteBomb newremoteBomb;

    // set X & Y in Grid
    int GridX = (int)(x / 32);
    int GridY = (int)(y / 32);

    // return if not on floor element
    if (currentMap.data[GridY][GridX] != TILE_FLOOR) return;

    // position bomb in grid
    newremoteBomb.posx = GridX * 32;
    newremoteBomb.posy = GridY * 32;

    // set bomb properties
    newremoteBomb.owner = owner;

    // add bomb to bomblist
    remoteBombList.push_back(newremoteBomb);

    //sorry wegen der komplizierten schaltung sie giebt nur den detinator
    if (owner != nullptr && !owner->hasItem(remotebombdetonator)) {
        owner->addItem(remotebombdetonator, 1);
    }
}
void drawremoteBomb() {
    for (const auto& bomb : remoteBombList) {
        float scale = 26.0f / textures["remotebomb"].width;
        float drawX = (float)bomb.posx - (textures["remotebomb"].width * scale) / 2.0f;
        float drawY = (float)bomb.posy - (textures["remotebomb"].height * scale) / 2.0f;

        DrawTextureEx(textures["remotebomb"], { drawX + 16, drawY + 16 }, 0, scale, WHITE);
    }
}

void explodeRemoteBomb(Player* owner) {
    for (auto& bomb : remoteBombList) {
        if (bomb.owner == owner) {
            bombExplode(bomb.posx, bomb.posy, owner->getBombRange(), owner);
        }
    }
    
    remoteBombList.erase(
        std::remove_if(remoteBombList.begin(), remoteBombList.end(),
            [owner](const remoteBomb& b) {
                return b.owner == owner;
            }),
        remoteBombList.end()
    );
}