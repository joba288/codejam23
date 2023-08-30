#include <iostream>
#include <vector>
#include <memory> // THE THEME!!! Also TODO

#include <cmath>
#include <ctime>

#include "raylib.h"

#include "./Person.h"
#include "./Scene.h"
#include "./GameScenes.h"

int main(void)
{
    // -------------------------------------------------------------------------------    
    // Initialization
    // -------------------------------------------------------------------------------
    constexpr int screenWidth = 1080;
    constexpr int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "Memory");
    SetTargetFPS(60);
    srand(time(NULL));

    // -------------------------------------------------------------------------------
    // Scene management
    // -------------------------------------------------------------------------------
    SceneManager sm;
    MenuScene menu(&sm);
    MainScene main(&sm);
    sm.PushScene(&menu);
    sm.PushScene(&main);

    

    // -------------------------------------------------------------------------------
    // Main game loop
    // -------------------------------------------------------------------------------
    while (!WindowShouldClose())
    {
        sm.RunScene(GetFrameTime());
    }

    // -------------------------------------------------------------------------------
    // Fin
    // -------------------------------------------------------------------------------
    CloseWindow();
    return 0;
}
