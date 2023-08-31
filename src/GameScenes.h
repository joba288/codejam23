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

class ChooseTargetScene : public Scene
{
    public:
        ChooseTargetScene(SceneManager *sm) : Scene(sm)
        {
            srand(time(NULL));
            sceneManager = sm;
            targetPerson.push_back(Person(Vector2{1024/2, 768/2}));
        }
    private:
        Randomiser r;
        std::vector<Person>targetPerson;
        Scene* nextScene;
        SceneManager *sceneManager;
        bool init = true;
        void Tick(float deltaTime) override
        {

            if (init){
                sceneManager->targetSeed = rand() % 100000;
                targetPerson[0] = Person(Vector2{1024/2, 768/2});
                init = false;
            }

            if (IsKeyPressed(KEY_SPACE)) {
               SwitchScene(2);
               init = true;
            }

            BeginDrawing();

            ClearBackground(RAYWHITE);

            targetPerson[0].Draw(); 
            
            EndDrawing();
        }
};


class MainScene : public Scene
{
public:
    MainScene(SceneManager *sm) : Scene(sm)
    {
        sceneManager = sm;

        srand(time(NULL));      


    }


private:

    // Defining our scene-specific members
    Randomiser r;
    std::vector<Person> persons;
    Person *m_lastHovered = nullptr;
    SceneManager *sceneManager;
    bool init = true;
    void Tick(float deltaTime) override
    {
        // -- initialise only once (so that restarting it possible)
        if (init)
        {
            persons = createCrowd(20, r); // idk how bad on memory this will be but its once a scene so

            // -- create target person
            persons.push_back(Person(Vector2{(float)(rand() % 1000), (float)(rand() % 1000)}));

            init = false;
        }
        // ----------------------------------------------------------

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

        if (IsKeyPressed(KEY_SPACE)){ SwitchScene(1); init = true; }            // -- go back to choose target scene            
        if (IsKeyPressed(KEY_R)) init = true;                                   // -- restart scene


        BeginDrawing();

        ClearBackground(RAYWHITE);
        std::cout << persons.size() << std::endl;
        for (auto &person : persons) {
            person.Draw();
        }
        
        EndDrawing();
    }

    std::vector<Person> createCrowd(int amount, Randomiser r){
        std::vector<Person> persons;

        for (int i = 0; i < amount; i++) {         
            persons.push_back(Person(Vector2{(float)(rand() % 1000), (float)(rand() % 1000)}));
        }
        
        return persons;
    }
};
