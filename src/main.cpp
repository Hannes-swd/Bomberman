#include "raylib.h"
#include "globals.h"
#include "map.h"
#include "player.h"
#include "cam.h"
#include "Ui.h"
#include "textures.h"
#include "item.h"

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
    InitMap();
    Player player1(1 * 32 + 16, 1 * 32 + 16);
    Player player2((width-2) * 32 + 16, (height-2) * 32 + 16);

    int lastWidth = GetScreenWidth();
    int lastHeight = GetScreenHeight();

    player1.addItem(stone, 1);
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
        //coleckts dropped items
        colecktItem(player1, player2);
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            beginCamera();

            ClearBackground(WHITE);
            DrawMap();

            deleteBomb();

            DrawItems();
            drawBomb();

            player1.drawPlayer(PLAYER_ONE);
            player2.drawPlayer(PLAYER_TWO);

            if(player1.HP > 0 && player2.HP > 0){
                playermoovment(player1, player2);
                DrawLives(player1, player2);
                DrawInv(player1, player2);
            } else {
                DrawDeathScreen();
            }

            endCamera();
            
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