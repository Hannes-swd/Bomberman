#include "bomb.h" // include class from bom.h
#include <raylib.h>
#include <iostream>

// function to add bomb element
void placeBomb(int x, int y) {
    std::cout << "bombe platziert";
    Bomb newBomb;
    newBomb.posX = x;
    newBomb.posY = y;
    BombList.push_back(newBomb);
}

// function to draw bombs
void drawBomb() {
    for (const auto& Bomb : BombList) {
        DrawCircle(Bomb.posX,Bomb.posY , 15, BLACK);
    }
}

std::vector<Bomb> BombList;
