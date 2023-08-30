#pragma once
#include "raylib.h"
#include "./Scene.h"
#include <vector>
#include "./Person.h"
#include "./Randomiser.h"

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

        srand(time(NULL));

        targetPerson.push_back(r.createRandomPerson(1, Vector2{0.f}));
       


    }


private:

    // Defining our scene-specific members
    Randomiser r;
    std::vector<Person> persons;
    std::vector<Person>targetPerson; // because fuckin cpp wont allow me to create and empty person variable
    
    Person *m_lastHovered = nullptr;

    bool init = true;
    void Tick(float deltaTime) override
    {
        // -- initialise only once (so that restarting it possible)
        if (init)
        {
            persons = createCrowd(20, r); // idk how bad on memory this will be but its once a scene so

            // -- create target person
            int targetSeed = rand() % 100000;
            persons.push_back(r.createRandomPerson(targetSeed, Vector2{(float)(rand() % 1000), (float)(rand() % 1000)}));
            targetPerson[0] = (r.createRandomPerson(targetSeed, Vector2{1000.f, 50.f}));
            targetPerson[0].scale = 0.5f; //temp gui element

            init = false;
        }

        m_lastHovered = nullptr;

        // -- Our Layering Problems are Over -- (yay !!)
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
        if (IsKeyPressed(KEY_R))
        {
             SwitchScene(1);
             init = true;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);
        std::cout << persons.size() << std::endl;
        for (auto &person : persons) {
            person.Draw();
        }

        targetPerson[0].Draw(); 
        
        EndDrawing();
    }

    std::vector<Person> createCrowd(int amount, Randomiser r){
        std::vector<Person> persons;

        for (int i = 0; i < amount; i++) {         
            persons.push_back(r.createRandomPerson(rand() % 100000, Vector2{(float)(rand() % 1000), (float)(rand() % 1000)}));
        }
        
        return persons;

    }
};
