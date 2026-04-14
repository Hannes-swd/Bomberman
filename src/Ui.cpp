#include "raylib.h"
#include "player.h"

void DrawLives(const Player& player1, const Player& player2) {

    int P1HP = player1.getPlayerLive();
    int P2HP = player2.getPlayerLive();

    int maxHP = 10;

    int barWidth = 100;
    int barHeight = 10;

    // ---------------- PLAYER 1 ----------------
    float p1Ratio = (float)P1HP / maxHP;

    DrawRectangle(
        player1.getPositionX() - 40,
        player1.getPositionY() - 40,
        barWidth,
        barHeight,
        DARKGRAY
    );

    DrawRectangle(
        player1.getPositionX() - 40,
        player1.getPositionY() - 40,
        barWidth * p1Ratio,
        barHeight,
        BLUE
    );

    // ---------------- PLAYER 2 ----------------
    float p2Ratio = (float)P2HP / maxHP;

    DrawRectangle(
        player2.getPositionX() - 40,
        player2.getPositionY() - 40,
        barWidth,
        barHeight,
        DARKGRAY
    );

    DrawRectangle(
        player2.getPositionX() - 40,
        player2.getPositionY() - 40,
        barWidth * p2Ratio,
        barHeight,
        RED
    );
}