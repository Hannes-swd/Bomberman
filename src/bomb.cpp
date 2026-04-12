#include "bomb.h" // include class from bom.h
#include <raylib.h>
#include <iostream>

// function to add bomb element
void placeBomb(int x, int y) {
    Bomb newBomb;

    newBomb.posX = (int)(x / 32) * 32;
    newBomb.posY = (int)(y / 32) * 32;
    newBomb.spawnTime = GetTime();

    BombList.push_back(newBomb);
}

// function to draw bombs
void drawBomb() {
    for (const auto& Bomb : BombList) {
        DrawCircle(Bomb.posX + 16,Bomb.posY + 16 , 15, BLACK);
    }
}

// function to erese bomb
void deleteBomb() {
    double now = GetTime();

    BombList.erase(
        std::remove_if(BombList.begin(), BombList.end(),
            [now](const Bomb& b) {
                return (now - b.spawnTime) >= 5.0;
            }),
            BombList.end()
    );
}

std::vector<Bomb> BombList;
