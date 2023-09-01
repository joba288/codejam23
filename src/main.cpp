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

    // TODO:
    // - [ ] Group static window information into small structure
    // - [ ] Un-hard-code all of this information accordingly
    // ...after this, there should be no problem adjusting resolution
    constexpr int screenWidth = 1080;
    constexpr int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "Memory");
    InitAudioDevice();
    SetTargetFPS(60);
    srand(time(NULL));


    // -------------------------------------------------------------------------------
    // Shader Loading
    // -------------------------------------------------------------------------------
    Person::dissolveShader = LoadShader("resources/shaders/dissolve.vs", "resources/shaders/dissolve.fs");
    Person::dissolveTimeLoc = GetShaderLocation(Person::dissolveShader, "dissolveTime");

    // -- really could do with a shader manager but its not worth it at this point in the project

    Sound dissolveSound = LoadSound("resources/sounds/dissolve.wav");
    Person::dissolveSound = &dissolveSound;

    // -------------------------------------------------------------------------------
    // Scene management
    // -------------------------------------------------------------------------------
    SceneManager sm;
    MenuScene menu(&sm);
    ChooseTargetScene chooseTargetScene(&sm);
    MainScene main(&sm);
    sm.PushScene(&menu);
    sm.PushScene(&chooseTargetScene);
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
