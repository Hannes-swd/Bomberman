#include "raylib.h"
#include "player.h"
#include "textures.h"


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
void DrawInv(const Player& player1, const Player& player2) {
    int iconSize = 24;
    
    // Inventar für Spieler 1 zeichnen
    int startX = (int)player1.getPositionX() - 60;
    int startY = (int)player1.getPositionY() - 55;
    int spacing = 32;
    
    for (size_t i = 0; i < player1.inventarListe.size(); i++) {
        const auto& slot = player1.inventarListe[i];
        int x = startX + (int)(i * spacing);
        int y = startY;
        
        Rectangle destRect = { 
            (float)x - (iconSize / 2.0f), 
            (float)y - (iconSize / 2.0f), 
            (float)iconSize, 
            (float)iconSize 
        };
        
        // Direkte Verwendung der Textur aus dem globalen textures-Objekt
        if (slot.item == stone) {
            Rectangle srcRect = { 0, 0, (float)textures["stone"].width, (float)textures["stone"].height };
            DrawTexturePro(textures["stone"], srcRect, destRect, {0, 0}, 0, WHITE);
        } else {
            DrawRectangle(destRect.x, destRect.y, iconSize, iconSize, GRAY);
        }
        
        // Anzahl anzeigen
        char countText[10];
        sprintf_s(countText, sizeof(countText), "%d", slot.count);
        int textWidth = MeasureText(countText, 14);
        DrawText(countText, x - textWidth/2, y + iconSize/2 - 4, 14, WHITE);
    }
    
    // Inventar für Spieler 2 zeichnen
    startX = (int)player2.getPositionX() - 60;
    startY = (int)player2.getPositionY() - 55;
    
    for (size_t i = 0; i < player2.inventarListe.size(); i++) {
        const auto& slot = player2.inventarListe[i];
        int x = startX + (int)(i * spacing);
        int y = startY;
        
        Rectangle destRect = { 
            (float)x - (iconSize / 2.0f), 
            (float)y - (iconSize / 2.0f), 
            (float)iconSize, 
            (float)iconSize 
        };
        
        if (slot.item == stone) {
            Rectangle srcRect = { 0, 0, (float)textures["stone"].width, (float)textures["stone"].height };
            DrawTexturePro(textures["stone"], srcRect, destRect, {0, 0}, 0, WHITE);
        } else {
            DrawRectangle(destRect.x, destRect.y, iconSize, iconSize, GRAY);
        }
        
        char countText[10];
        sprintf_s(countText, sizeof(countText), "%d", slot.count);
        int textWidth = MeasureText(countText, 14);
        DrawText(countText, x - textWidth/2, y + iconSize/2 - 4, 14, WHITE);
    }
}