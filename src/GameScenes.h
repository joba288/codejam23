#pragma once

#include <vector>
#include <string>
#include <string_view>

#include "raylib.h"
#include "./Scene.h"
#include "./Person.h"
#include "./Randomiser.h"
#include "./Bin.h"
#include "./TextBox.h"

class MenuScene : public Scene
{
    TextBox tb;
public:
    // Initializing members only once, ever
    MenuScene(SceneManager *sm)
        : Scene(sm),
          tb(0.04f)
    {}
    void Init() override
    {
        tb.Reset();
        tb.Play();
    }
    
    void Tick(float deltaTime) override
    {
        if (IsKeyPressed(KEY_SPACE)) {
            SwitchScene(1);
        }
        BeginDrawing();
        ClearBackground(WHITE);
        tb.Update();
        DrawText("Please press space to begin", 100, 250, 45, RED);
        EndDrawing();
    }
};

class ChooseTargetScene : public Scene
{
public:
    inline static PersonGraphics target;
    ChooseTargetScene(SceneManager *sm) : Scene(sm)
    {
        targetPerson.push_back(Person(Vector2{1024/2, 768/2}));
    }
private:
    Randomiser r;
    // I'm only keeping this so that we can have multiple sometime
    // and I believe you were thinking the same as well (yes i was)
    std::vector<Person>targetPerson;

    float maxStudyTime;
    float timeRemaining;

    void Done()
    {
        if (maxStudyTime > 1.f) maxStudyTime -= 0.1f;
        else maxStudyTime = 1.f;
        NextScene();
    }

    void Init() override
    {
        timeRemaining = maxStudyTime;
        timeRemaining = 5.0f;
        maxStudyTime = 5.0f;

        PersonGraphics targetGraphics = Randomiser::CreateRandomPerson();
        ChooseTargetScene::target = targetGraphics;
        targetPerson[0] = Person(Vector2{1024/2, 768/2}, targetGraphics);
    }

    void Tick(float deltaTime) override
    {
        if (timeRemaining <= 0.f || IsKeyPressed(KEY_SPACE)) Done();
        
        BeginDrawing();

        ClearBackground(RAYWHITE);

        targetPerson[0].Draw();
        DrawText(TextFormat("Remaining: %.2f", timeRemaining), 10, 10, 40, RED);

        EndDrawing();

        timeRemaining -= deltaTime; // GetFrameTime() also accessible
    }
};

class MainScene : public Scene
{
public:
    // TODO maybe move everything to static members of each class
    MainScene(SceneManager *sm)
        : Scene(sm),
          bin(Bin(LoadTexture("resources/bin_closed.png"), LoadTexture( "resources/bin_open.png")))
    {
        bin.rect.x = 25.f;
        bin.rect.y = 750 - bin.rect.height;
    }
private:

    Bin bin;
    std::vector<Person> persons;
    Person *m_lastHovered = nullptr;

    float m_maxTime = 20.f;
    float m_timer = m_maxTime;

    int crowdNumber = 20;
    int targetIndex;

    void Init() override
    {
        Person::somethingGrabbed = false;
        m_timer = m_maxTime;

        // -- Generate the crowd --
        persons = createCrowd(crowdNumber);
        
        // -- Create target Person --
        // TODO: Wasteful approach, please clean up, I'm sick and tired
        // i.e. we're resetting one when we can just set it in the first place
        targetIndex = rand() % crowdNumber;
        persons[targetIndex] = Person(Vector2{(float)(75 + (rand() % 930)), (float)(150 + (rand() % 300))}, ChooseTargetScene::target, true);
    }

    void Tick(float deltaTime) override
    {
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

        if (IsKeyPressed(KEY_SPACE)){ PreviousScene(); } // Regenerate target
        if (IsKeyPressed(KEY_R)) Init(); // Regenerate crowd

        BeginDrawing();
        ClearBackground(RAYWHITE);
        // std::cout << persons.size() << std::endl;
        bin.Draw();
        for (auto &person : persons) {
            person.Draw();
        }
        // If target in crowd, `crowdNumber - 1` please
        persons[targetIndex].DrawDebug();


        DrawText(TextFormat("Remaining: %.2f", m_timer), 10, 10, 40, RED);
        DrawFPS(20, 20);

        EndDrawing();

        // Timer things
        m_timer -= deltaTime;
        if (m_timer <= 0.f) { SwitchScene(0); }
    }

    std::vector<Person> createCrowd(int amount){
        std::vector<Person> persons;

        for (int i = 0; i < amount; i++) {         
            persons.push_back(Person(Vector2{(float)(75 + (rand() % 930)), (float)(150 + (rand() % 300))}));
        }
        
        return persons;
    }
};
