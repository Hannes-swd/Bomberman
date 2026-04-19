#include "player.h"
#include "raylib.h"

void DrawLives(const Player& player1, const Player& player2);
void DrawInv(const Player& player1, const Player& player2);
void DrawSelectedItemFrame(const Player& player, int startX, int startY, int spacing, int iconSize);