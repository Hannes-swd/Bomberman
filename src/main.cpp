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

    Curent_map_Size = map_Medium;
    
    Player player1(1 * 32 + 16, 1 * 32 + 16);
    Player player2((width-2) * 32 + 16, (height-2) * 32 + 16);

    int lastWidth = GetScreenWidth();
    int lastHeight = GetScreenHeight();
    InitMap();
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

        if (IsKeyPressed(KEY_V)) {
            if (Curent_map_Size == map_Medium)
                Curent_map_Size = map_Big;
            else if (Curent_map_Size == map_Big)
                Curent_map_Size = map_Small;
            else if (Curent_map_Size == map_Small)
                Curent_map_Size = map_Medium;
            
            InitMap();
            
            player1.setplayer(1 * 32 + 16, 1 * 32 + 16);
            player2.setplayer((currentMap.width-2) * 32 + 16, (currentMap.height-2) * 32 + 16);
            
            BombList.clear();
            
            managecam();
        }
        
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

            player1.drawPlayer(PLAYER_ONE);
            player2.drawPlayer(PLAYER_TWO);

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