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


void DrawSelectedItemFrame(const Player& player, int startX, int startY, int spacing, int iconSize) {
    int selectedIndex = player.getSelectedItemIndex();
    if (selectedIndex >= 0 && selectedIndex < (int)player.inventarListe.size()) {
        int frameX = startX + selectedIndex * spacing;
        int frameY = startY;
        
        DrawRectangleLines(frameX - 2, frameY - 2, iconSize + 4, iconSize + 4, YELLOW);
        DrawRectangleLines(frameX - 1, frameY - 1, iconSize + 2, iconSize + 2, GOLD);
    }
}

void DrawInv(const Player& player1, const Player& player2) {
    int iconSize = 24;
    int spacing = 32;
    
    // Inventar player 1
    int itemCount1 = (int)player1.inventarListe.size();
    if (itemCount1 > 0) {
        int totalWidth = (itemCount1 - 1) * spacing + iconSize;
        
        int startX = (int)player1.getPositionX() - (totalWidth / 2);
        int startY = (int)player1.getPositionY() - 70;
        
        for (size_t i = 0; i < player1.inventarListe.size(); i++) {
            const auto& slot = player1.inventarListe[i];
            int x = startX + (int)(i * spacing) + (iconSize / 2);
            int y = startY + (iconSize / 2);
            
            Rectangle destRect = { 
                (float)x - (iconSize / 2.0f), 
                (float)y - (iconSize / 2.0f), 
                (float)iconSize, 
                (float)iconSize 
            };
            
            if (slot.item == stone) {
                Rectangle srcRect = { 0, 0, (float)textures["stone"].width, (float)textures["stone"].height };
                DrawTexturePro(textures["stone"], srcRect, destRect, {0, 0}, 0, WHITE);
            }
            else if (slot.item == mine) {
                Rectangle srcRect = { 0, 0, (float)textures["mine"].width, (float)textures["mine"].height };
                DrawTexturePro(textures["mine"], srcRect, destRect, {0, 0}, 0, WHITE);
            }
            else if (slot.item == remotebomb) {
                Rectangle srcRect = { 0, 0, (float)textures["remotebomb"].width, (float)textures["remotebomb"].height };
                DrawTexturePro(textures["remotebomb"], srcRect, destRect, {0, 0}, 0, WHITE);
            }
            else if (slot.item == remotebombdetonator) {
                Rectangle srcRect = { 0, 0, (float)textures["remotebombdetonator"].width, (float)textures["remotebombdetonator"].height };
                DrawTexturePro(textures["remotebombdetonator"], srcRect, destRect, {0, 0}, 0, WHITE);
            }else if (slot.item == HealingPotion) {
                Rectangle srcRect = { 0, 0, (float)textures["HealingPotion"].width, (float)textures["HealingPotion"].height };
                DrawTexturePro(textures["HealingPotion"], srcRect, destRect, {0, 0}, 0, WHITE);
            } else {
                DrawRectangle(destRect.x, destRect.y, iconSize, iconSize, ORANGE);
            }
            
            char countText[10];
            sprintf_s(countText, sizeof(countText), "%d", slot.count);
            int textWidth = MeasureText(countText, 14);
            DrawText(countText, x - textWidth/2, y + iconSize/2 - 4, 14, WHITE);
        }
        //draw ramen
        DrawSelectedItemFrame(player1, startX, startY, spacing, iconSize);
    }
    
    // Inventar player 2
    int itemCount2 = (int)player2.inventarListe.size();
    if (itemCount2 > 0) {
        int totalWidth = (itemCount2 - 1) * spacing + iconSize;
        
        int startX = (int)player2.getPositionX() - (totalWidth / 2);
        int startY = (int)player2.getPositionY() - 70;
        
        for (size_t i = 0; i < player2.inventarListe.size(); i++) {
            const auto& slot = player2.inventarListe[i];
            int x = startX + (int)(i * spacing) + (iconSize / 2);
            int y = startY + (iconSize / 2);
            
            Rectangle destRect = { 
                (float)x - (iconSize / 2.0f), 
                (float)y - (iconSize / 2.0f), 
                (float)iconSize, 
                (float)iconSize 
            };
            
            if (slot.item == stone) {
                Rectangle srcRect = { 0, 0, (float)textures["stone"].width, (float)textures["stone"].height };
                DrawTexturePro(textures["stone"], srcRect, destRect, {0, 0}, 0, WHITE);
            }else if (slot.item == mine) {
                Rectangle srcRect = { 0, 0, (float)textures["mine"].width, (float)textures["mine"].height };
                DrawTexturePro(textures["mine"], srcRect, destRect, {0, 0}, 0, WHITE);
            }else if (slot.item == HealingPotion) {
                Rectangle srcRect = { 0, 0, (float)textures["HealingPotion"].width, (float)textures["HealingPotion"].height };
                DrawTexturePro(textures["HealingPotion"], srcRect, destRect, {0, 0}, 0, WHITE);
            } else {
                DrawRectangle(destRect.x, destRect.y, iconSize, iconSize, ORANGE);
            }
            
            char countText[10];
            sprintf_s(countText, sizeof(countText), "%d", slot.count);
            int textWidth = MeasureText(countText, 14);
            DrawText(countText, x - textWidth/2, y + iconSize/2 - 4, 14, WHITE);
        }
        
        // draw ramen
        DrawSelectedItemFrame(player2, startX, startY, spacing, iconSize);
    }
}