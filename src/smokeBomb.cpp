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

        if (elapsed < cloud.duration) {

            // Fade-Out
            float intensity = 1.0f - (elapsed / cloud.duration);

            Color smokeColor = {
                20,
                20,
                20,
                245
            };

            // 5x5 Bereich
            for (int offsetX = -4; offsetX <= 4; offsetX++) {
                for (int offsetY = -4; offsetY <= 4; offsetY++) {

                    int currentX = cloud.posx + (offsetX * 32);
                    int currentY = cloud.posy + (offsetY * 32);

                    DrawRectangle(
                        currentX,
                        currentY,
                        32,
                        32,
                        smokeColor
                    );
                }
            }
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
            newCloud.duration = 15.0f;
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
            newCloud.duration = 15.0f;
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