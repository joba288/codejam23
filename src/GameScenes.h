#pragma once
#include "raylib.h"
#include "./Scene.h"
#include <vector>
#include "./Person.h"

class MenuScene : public Scene
{
 public:
    MenuScene(SceneManager *sm) : Scene(sm) {}
    void Tick(float deltaTime) override
    {
        if (IsKeyPressed(KEY_SPACE)) {
            SwitchScene(1);
        }
        BeginDrawing();
        ClearBackground(WHITE);
        DrawText("Please press space to begin", 100, 250, 45, RED);
        EndDrawing();
    }
};

class MainScene : public Scene
{
public:
    MainScene(SceneManager *sm) : Scene(sm)
    {

        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        // MAJOR TODO: Make these static ("static"?) arrays within a Randomizer class
        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
    }
private:

    // Defining our scene-specific members
    std::vector<Person> persons;
    Person *m_lastHovered = nullptr;
    void Tick(float deltaTime) override
    {
        m_lastHovered = nullptr;

        // -- Our Layering Problems are Over --
        for (auto &person : persons) {
            // Get topmost Person we are hovering over
            if (person.IsMouseOver()) m_lastHovered = &person;
        }

        for (auto &person : persons) {
            // Only allow drag-n-drop behaviour when topmost one!
            bool shouldSelect = m_lastHovered == &person;
            person.Update(GetTime(), shouldSelect);
        }
        // ------------------------------------

        if (IsKeyPressed(KEY_SPACE)) OpenURL("https://youtube.com/@joba2888");

        BeginDrawing();

        ClearBackground(RAYWHITE);
        std::cout << persons.size() << std::endl;
        for (auto &person : persons) {
            person.Draw();
        }

        EndDrawing();
    }
};
