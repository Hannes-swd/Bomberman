#include "raylib.h"
#include "globals.h"
#include "map.h"
#include "textures.h"

/*
    - 0 = floor (laufbar)
    - 1 = Wall (zerstörbar)
    - 2 = Bedrock (nicht zerstörbar)
    - 3 = Bomb
*/

MapData currentMap;
std::string textDisplay;
Color textColor;

void InitMap() {
    
    
    switch (Curent_map_Size) {
        case map_Small:
            width = 13;
            height = 7;
            break;
        case map_Medium:
            width = 29;
            height = 15;
            break;
        case map_Big:
            width = 39;
            height = 21;
            break;
    }
    
    // Vector mit Größe height, jeder Eintrag ein vector<Tiles> mit Größe width
    currentMap.data.assign(height, std::vector<Tiles>(width, TILE_FLOOR));
    currentMap.width = width;
    currentMap.height = height;
    
    // Map befüllen
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (y == 0 || y == height-1 || x == 0 || x == width-1) {
                currentMap.data[y][x] = TILE_BEDROCK;
            }
            else if (x % 2 == 0 && y % 2 == 0) {
                currentMap.data[y][x] = TILE_BEDROCK;
            }
            else {
                if (GetRandomValue(0, 99) < 50) {
                    currentMap.data[y][x] = TILE_WALL;
                } else {
                    currentMap.data[y][x] = TILE_FLOOR;
                }
            }
        }
    }
    //oben links
    currentMap.data[1][1] = TILE_FLOOR;    
    currentMap.data[1][2] = TILE_FLOOR; 
    currentMap.data[2][1] = TILE_FLOOR;     
    
    //unten rechts
    currentMap.data[height-2][width-2] = TILE_FLOOR; 
    currentMap.data[height-3][width-2] = TILE_FLOOR; 
    currentMap.data[height-2][width-3] = TILE_FLOOR; 
}

void DrawMap() {
    int blockSize = 32;
    
    for (int y = 0; y < currentMap.height; y++) {
        for (int x = 0; x < currentMap.width; x++) {
            Rectangle destRect = { 
                (float)(x * blockSize), 
                (float)(y * blockSize), 
                (float)blockSize, 
                (float)blockSize 
            };
            
            if (currentMap.data[y][x] == TILE_WALL) {
                Rectangle srcRect = { 0, 0, (float)textures["stone"].width, (float)textures["stone"].height };
                DrawTexturePro(textures["stone"], srcRect, destRect, {0, 0}, 0, WHITE);
            }
            else if (currentMap.data[y][x] == TILE_BEDROCK) {
                Rectangle srcRect = { 0, 0, (float)textures["bedrock"].width, (float)textures["bedrock"].height };
                DrawTexturePro(textures["bedrock"], srcRect, destRect, {0, 0}, 0, WHITE);
            }
            else {
                DrawRectangle(x * blockSize, y * blockSize, blockSize, blockSize, DARKGREEN);
            }
        }
    }
}

void DrawDeathScreen(std::string color){
    int screenW = width * 32;
    int screenH = height * 32;
    int centerX = screenW / 2;
    int centerY = screenH / 2;

    std::string colorText = (color == "RED") ? "SPIELER 2" : "SPIELER 1";
    Color textColor = (color == "RED") ? RED : BLUE;
    std::string player = (color == "RED") ? "player2win" : "player1win";

    int FontSize = 16;
    float PlayerSize = 64.0f;

    if (width == 13) {        
        FontSize = 16;
        PlayerSize = 44.0f;
    }
    else if (width == 29){
        FontSize = 32;
        PlayerSize = 96.0f;
    }
    else if (width == 39){
        FontSize = 48;
        PlayerSize = 144.0f;
    }

    int colorTextW = MeasureText(colorText.c_str(), FontSize);
    int winTextW   = MeasureText("HAT GEWONNEN", FontSize);

    DrawRectangle(0, 0, screenW, screenH, Fade(BLACK, 0.6f));

    float scale = PlayerSize / textures[player].width;
    float drawX = (float)centerX - (textures[player].width * scale) / 2.0f;
    float drawY = (float)centerY / 1.65 - (textures[player].height * scale) / 2.0f;
    DrawTextureEx(textures[player], { drawX, drawY }, 0, scale, WHITE);

    DrawText(colorText.c_str(), centerX - colorTextW / 2, centerY - FontSize, FontSize, textColor);
    DrawText("HAT GEWONNEN",    centerX - winTextW  / 2,  centerY + 2, FontSize,   WHITE);
}