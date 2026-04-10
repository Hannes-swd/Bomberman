#include "raylib.h"
#include "globals.h"
#include "map.h"
#include "player.h"

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

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    
    Curent_map_Size = map_Small;
    InitMap();
    Player player1(10, 10);
    Player player2(500, 500);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(WHITE);
            DrawMap();

            drawBomb();

            player1.drawPlayer(RED);
            player2.drawPlayer(BLUE);

            if(IsKeyDown(KEY_W))
                player1.moveUp();
            
            if(IsKeyDown(KEY_S))
                player1.moveDown();

            if(IsKeyDown(KEY_A))
                player1.moveLeft();
            
            if(IsKeyDown(KEY_D))
                player1.moveRight();


            if(IsKeyDown(KEY_UP))
                player2.moveUp();
            
            if(IsKeyDown(KEY_DOWN))
                player2.moveDown();

            if(IsKeyDown(KEY_LEFT))
                player2.moveLeft();
            
            if(IsKeyDown(KEY_RIGHT))
                player2.moveRight();

            if(IsKeyPressed(KEY_TAB))
                player1.setBomb();

            if(IsKeyPressed(KEY_RIGHT_SHIFT)){
                player2.setBomb();
            }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}