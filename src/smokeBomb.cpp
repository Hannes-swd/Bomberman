#include <vector>
#include <algorithm>
#include <cmath>
#include "raylib.h"
#include "smokeBomb.h"
#include "textures.h"
#include "player.h"
#include "map.h"
#include "bomb.h"

std::vector<SmokeBomb> smokeBombList;
std::vector<SmokeCloud> smokeCloudList;

void placeSmokeBomb(int x, int y, Player* owner) {
    SmokeBomb newsmokeBomb;

    int GridX = (int)(x / 32);
    int GridY = (int)(y / 32);
    
    // Prüfen ob auf Boden platziert werden kann
    if (currentMap.data[GridY][GridX] != TILE_FLOOR) return;

    newsmokeBomb.posx = GridX * 32;
    newsmokeBomb.posy = GridY * 32;
    newsmokeBomb.owner = owner;
    newsmokeBomb.explosionTime = GetTime();

    smokeBombList.push_back(newsmokeBomb);
}

void drawSmokeBomb() {
    for (const auto& bomb : smokeBombList) {
        double now = GetTime();
        if ((now - bomb.explosionTime) < 0.2) {
            float scale = 26.0f / textures["smokebomb"].width;
            float drawX = (float)bomb.posx - (textures["smokebomb"].width * scale) / 2.0f;
            float drawY = (float)bomb.posy - (textures["smokebomb"].height * scale) / 2.0f;
            DrawTextureEx(textures["smokebomb"], { drawX + 16, drawY + 16 }, 0, scale, WHITE);
        }
    }
}

void drawSmokeClouds() {
    double now = GetTime();
    
    for (const auto& cloud : smokeCloudList) {
        float elapsed = (float)(now - cloud.startTime);
        float remaining = (float)(cloud.duration - elapsed);
        
        if (remaining > 0) {
            // Intensität des Rauchs (am Anfang stärker)
            float intensity = (remaining / (float)cloud.duration);
            
            // Rauchfarbe: Dunkelgrau bis Hellgrau
            Color smokeColor;
            smokeColor.r = 80;
            smokeColor.g = 80;
            smokeColor.b = 80;
            smokeColor.a = (unsigned char)(220 * intensity);
            
            // Rauchbereich - 3x3 Grid Bereich (wie bei Explosion)
            for (int offsetX = -1; offsetX <= 1; offsetX++) {
                for (int offsetY = -1; offsetY <= 1; offsetY++) {
                    int currentX = cloud.posx + (offsetX * 32);
                    int currentY = cloud.posy + (offsetY * 32);
                    
                    // Wackeleffekt für den Rauch
                    float wobbleX = (float)(sin(now * 2.0f + offsetX) * 3.0f);
                    float wobbleY = (float)(cos(now * 2.0f + offsetY) * 3.0f);
                    
                    // Rauchintensität für Randbereiche reduzieren
                    float cellIntensity = intensity;
                    if (abs(offsetX) == 1 && abs(offsetY) == 1) {
                        cellIntensity = intensity * 0.7f;  // Ecken etwas schwächer
                    } else if (abs(offsetX) == 1 || abs(offsetY) == 1) {
                        cellIntensity = intensity * 0.85f; // Seiten etwas schwächer
                    }
                    
                    Color cellColor;
                    cellColor.r = 80;
                    cellColor.g = 80;
                    cellColor.b = 80;
                    cellColor.a = (unsigned char)(220 * cellIntensity);
                    
                    // Zeichne quadratischen Rauch (wie Explosion)
                    DrawRectangle(
                        currentX + (int)wobbleX,
                        currentY + (int)wobbleY,
                        32, 32,
                        cellColor
                    );
                    
                    // Zweite Schicht für mehr Deckung
                    if (cellIntensity > 0.5f) {
                        Color darkColor;
                        darkColor.r = 50;
                        darkColor.g = 50;
                        darkColor.b = 50;
                        darkColor.a = (unsigned char)(180 * cellIntensity);
                        
                        DrawRectangle(
                            currentX + (int)(wobbleX * 0.5f) + 4,
                            currentY + (int)(wobbleY * 0.5f) + 4,
                            24, 24,
                            darkColor
                        );
                    }
                }
            }
            
            // Zusätzliche Deckung für das Zentrum
            Color centerColor;
            centerColor.r = 60;
            centerColor.g = 60;
            centerColor.b = 60;
            centerColor.a = (unsigned char)(250 * intensity);
            
            float wobbleX = (float)(sin(now * 3.0f) * 3.0f);
            float wobbleY = (float)(cos(now * 2.5f) * 3.0f);
            
            DrawRectangle(
                cloud.posx + (int)wobbleX,
                cloud.posy + (int)wobbleY,
                32, 32,
                centerColor
            );
        }
    }
}

void updateSmokeClouds() {
    double now = GetTime();
    
    smokeCloudList.erase(
        std::remove_if(smokeCloudList.begin(), smokeCloudList.end(),
            [now](const SmokeCloud& cloud) {
                return (now - cloud.startTime) >= cloud.duration;
            }),
        smokeCloudList.end()
    );
}

void explodeSmokeBomb(Player* owner) {
    for (auto& bomb : smokeBombList) {
        if (bomb.owner == owner) {
            SmokeCloud newCloud;
            newCloud.posx = bomb.posx;
            newCloud.posy = bomb.posy;
            newCloud.startTime = GetTime();
            newCloud.duration = 5.0f;
            smokeCloudList.push_back(newCloud);
        }
    }
    
    smokeBombList.erase(
        std::remove_if(smokeBombList.begin(), smokeBombList.end(),
            [owner](const SmokeBomb& b) {
                return b.owner == owner;
            }),
        smokeBombList.end()
    );
}

void updateAllSmokes() {
    updateSmokeClouds();
    
    for (auto& bomb : smokeBombList) {
        if (GetTime() - bomb.explosionTime >= 0.05) {
            SmokeCloud newCloud;
            newCloud.posx = bomb.posx;
            newCloud.posy = bomb.posy;
            newCloud.startTime = GetTime();
            newCloud.duration = 5.0f;
            smokeCloudList.push_back(newCloud);
            
            bomb.explosionTime = 0;
        }
    }
    
    smokeBombList.erase(
        std::remove_if(smokeBombList.begin(), smokeBombList.end(),
            [](const SmokeBomb& b) {
                return b.explosionTime == 0;
            }),
        smokeBombList.end()
    );
}