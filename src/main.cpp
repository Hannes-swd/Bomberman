#include "raylib.h"
#include "globals.h"
#include "map.h"
#include "player.h"
#include "cam.h"
#include "Ui.h"
#include "textures.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    
    InitWindow(screenWidth, screenHeight, "Bomberman - raylib");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    

    loadTextures();

    Curent_map_Size = map_Big;
    InitMap();
    Player player1(1 * 32 + 16, 1 * 32 + 16);
    Player player2((width-2) * 32 + 16, (height-2) * 32 + 16);

    int lastWidth = GetScreenWidth();
    int lastHeight = GetScreenHeight();

    managecam();

    // Main game loop
    while (!WindowShouldClose()) 
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        int currentWidth = GetScreenWidth();
        int currentHeight = GetScreenHeight();
        
        if (currentWidth != lastWidth || currentHeight != lastHeight) {
            managecam();  // Kamera neu berechnen
            lastWidth = currentWidth;
            lastHeight = currentHeight;
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            beginCamera();

            ClearBackground(WHITE);
            DrawMap();

            deleteBomb();
            drawBomb();

            player1.drawPlayer(RED);
            player2.drawPlayer(BLUE);

            playermoovment(player1, player2);
            
            endCamera();
            DrawLives(player1, player2);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    unloadTextures();
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}