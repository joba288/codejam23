#include <iostream>
#include <cmath>

#include "raylib.h"



#include "./Person.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1080;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "Memory");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------


    Texture2D hair = LoadTexture("resources/hair1.png");
    Texture2D head = LoadTexture("resources/head1.png");
    Texture2D eyes = LoadTexture("resources/eyes1.png");
    Texture2D nose = LoadTexture("resources/nose1.png");
    Texture2D mouth = LoadTexture("resources/mouth1.png");
    Texture2D body = LoadTexture("resources/body1.png");
    Texture2D hand = LoadTexture("resources/hand1.png");
    Texture2D foot = LoadTexture("resources/foot1.png");

    Person person{Vector2{300.f, 300.f}, head, hair, eyes, nose, mouth, body, hand, foot, SKYBLUE, BROWN, PINK};




    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------




        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            person.Draw();
            person.scale = sin(GetTime());

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}