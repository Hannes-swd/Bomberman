#include "raylib.h"
#include "player.h"

void DrawLives(const Player& player1, const Player& player2) {
    int P1HP = player1.getPlayerLive();
    int P2HP = player2.getPlayerLive();
    
    DrawText(TextFormat("HP: %d", P1HP), 
             (int)player1.getPositionX() - 20, 
             (int)player1.getPositionY() - 30, 
             20, RED);
    DrawText(TextFormat("HP: %d", P2HP), 
             (int)player2.getPositionX() - 20, 
             (int)player2.getPositionY() - 30, 
             20, BLUE);
}