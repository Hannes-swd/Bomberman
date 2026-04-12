#include "raylib.h"
#include "player.h"

void DrawLives(const Player& player1, const Player& player2) {
    int P1HP = player1.getPlayerLive();
    int P2HP = player2.getPlayerLive();
    
    DrawText(TextFormat("Player 1 HP: %d", P1HP), 10, 10, 20, RED);
    DrawText(TextFormat("Player 2 HP: %d", P2HP), 10, 40, 20, BLUE);
}