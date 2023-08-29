#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>

#include "raylib.h"

#include "./Person.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    srand(time(NULL));
    
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1080;
    const int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "Memory");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
 


    std::vector<Texture2D> hairArray;
    std::vector<Texture2D> headArray;
    std::vector<Texture2D> eyesArray;
    std::vector<Texture2D> noseArray;
    std::vector<Texture2D> mouthArray;
    std::vector<Texture2D> bodyArray;
    std::vector<Texture2D> handArray;
    std::vector<Texture2D> footArray;

    hairArray.push_back(LoadTexture("resources/hair1.png"));
    hairArray.push_back(LoadTexture("resources/hair2.png"));

    headArray.push_back(LoadTexture("resources/head1.png"));

    eyesArray.push_back(LoadTexture("resources/eyes1.png"));
    eyesArray.push_back(LoadTexture("resources/eyes2.png"));

    noseArray.push_back(LoadTexture("resources/nose1.png"));
    noseArray.push_back(LoadTexture("resources/nose2.png"));

    mouthArray.push_back(LoadTexture("resources/mouth1.png"));

    bodyArray.push_back(LoadTexture("resources/body1.png"));
    
    handArray.push_back(LoadTexture("resources/hand1.png"));

    footArray.push_back(LoadTexture("resources/foot1.png"));

        
    std::vector<Person> persons;
    for (int i = 0; i < 20; i++) {
        persons.push_back(Person(
            Vector2{100.f + (float)(i * rand() % 1250), (float)(i * rand() % 1250)},
            headArray[rand() % headArray.size()], hairArray[rand() % hairArray.size()],
            eyesArray[rand() % eyesArray.size()], noseArray[rand() % noseArray.size()],
            mouthArray[rand() % mouthArray.size()], bodyArray[rand() % bodyArray.size()],
            handArray[rand() % handArray.size()], footArray[rand() % footArray.size()],
            (Color){ rand() % 255, rand() % 255, rand() % 255, 255 },
            (Color){ rand() % 255, rand() % 255, rand() % 255, 255 },
            (Color){ rand() % 255, rand() % 255, rand() % 255, 255 }
        ));
    }

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        for (auto &person : persons) person.Update(GetTime());


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            for (auto &person : persons) person.Draw();
                

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
