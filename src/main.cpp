#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <memory> // har har har

#include "raylib.h"

#include "./Person.h"
#include "./scene.h"

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


    Texture2D hair = LoadTexture("resources/hair1.png");
    Texture2D head = LoadTexture("resources/head1.png");
    Texture2D eyes = LoadTexture("resources/eyes1.png");
    Texture2D nose = LoadTexture("resources/nose1.png");
    Texture2D mouth = LoadTexture("resources/mouth1.png");
    Texture2D body = LoadTexture("resources/body1.png");
    Texture2D hand = LoadTexture("resources/hand1.png");
    Texture2D foot = LoadTexture("resources/foot1.png");

    std::cout << hair.width << ',' << hair.height << std::endl;
    std::cout << head.width << ',' << head.height << std::endl;
    std::cout << eyes.width << ',' << eyes.height << std::endl;
    std::cout << nose.width << ',' << nose.height << std::endl;
    std::cout << mouth.width << ',' << mouth.height << std::endl;
    std::cout << body.width << ',' << body.height << std::endl;
    std::cout << hand.width << ',' << hand.height << std::endl;
    std::cout << foot.width << ',' << foot.height << std::endl;
        
    std::vector<Person> persons;
    for (int i = 0; i < 20; i++) {
        persons.push_back(Person(
            Vector2{100.f + (float)(i * rand() % 1250), (float)(i * rand() % 1250)},
            head, hair, eyes, nose, mouth, body, hand, foot,
            (Color){ rand() % 255, rand() % 255, rand() % 255, 255 },
            (Color){ rand() % 255, rand() % 255, rand() % 255, 255 },
            (Color){ rand() % 255, rand() % 255, rand() % 255, 255 }
        ));
    }

    SceneManager sm;
    FooScene foo;
    BarScene bar;
    sm.PushScene(&foo);
    sm.PushScene(&bar);
    int idx = 0;
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        sm.RunScene(GetFrameTime());
        sm.SwitchScene(++idx % 2);

        for (auto &person : persons) person.Update(GetTime());

        if (IsKeyPressed(KEY_SPACE)) OpenURL("https://youtube.com/@joba2888");

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        for (auto &person : persons) {
            person.Draw();
            person.scale = (sin(GetTime() * 3.f) + 1.f) * 0.5f;
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
