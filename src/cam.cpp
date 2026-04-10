#include "cam.h"
#include "map.h"
#include "raylib.h"

Camera2D mainCam = { 0 };

void managecam() {
    int blockSize = 32;
    
    float mapWidth = (float)(currentMap.width * blockSize);
    float mapHeight = (float)(currentMap.height * blockSize);
    
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    
    float zoomX = (float)screenWidth / mapWidth;
    float zoomY = (float)screenHeight / mapHeight;
    mainCam.zoom = (zoomX < zoomY) ? zoomX : zoomY;
    
    mainCam.target.x = mapWidth / 2.0f;
    mainCam.target.y = mapHeight / 2.0f;
    
    mainCam.offset.x = (float)screenWidth / 2.0f;
    mainCam.offset.y = (float)screenHeight / 2.0f;
    
    mainCam.rotation = 0.0f;
}

void beginCamera() {
    BeginMode2D(mainCam);
}

void endCamera() {
    EndMode2D();
}