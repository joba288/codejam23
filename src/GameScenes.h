#pragma once

#include <vector>
#include <string>
#include <string_view>

#include "WindowInfo.h"
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
    inline static Music mainTheme;
    // Initializing members only once, ever
    MenuScene(SceneManager *sm)
        : Scene(sm),
          tb(0.04f, 100, 100)
    {
        mainTheme = LoadMusicStream("resources/music/finder.wav");
    }
    void Init() override
    {
        tb.Reset();
        tb.Play();
        PlayMusicStream(MenuScene::mainTheme);
    }
    
    void Tick(float deltaTime) override
    {
        UpdateMusicStream(MenuScene::mainTheme);
        if (IsKeyPressed(KEY_SPACE)) {
            NextScene();
        }
        BeginDrawing();
        ClearBackground(WHITE);
        tb.Update();
        DrawText("Proceed with [SPACE]", 100, 250, 45, RED);
        EndDrawing();
    }
};

class ChooseTargetScene : public Scene
{
public:
    inline static PersonGraphics target;
    ChooseTargetScene(SceneManager *sm) : Scene(sm), infoBox(0.02f, WINDOW_W * 0.425f, WINDOW_H * 0.45f)
    {
        targetPerson.push_back(Person(Vector2{0.f, 0.f}));
        infoBox.SetText("Your next client requests\n"
                        "that you eliminate this\n"
                        "person from their memory.\n"
                        "Please ensure that yours\n"
                        "does not fail you, and\n"
                        "note that this is a\n"
                        "highly sensitive\n"
                        "process.");
    }
private:
    Texture2D background;
    Randomiser r;
    // I'm only keeping this so that we can have multiple sometime
    // and I believe you were thinking the same as well (yes i was)
    std::vector<Person>targetPerson;

    // Too many study times!!!
    inline static constexpr float maxStudyTimeEver = 15.0f;
    float maxStudyTime = maxStudyTimeEver;
    float timeRemaining;

    TextBox infoBox;

    void Done()
    {
        if (maxStudyTime > 1.f) maxStudyTime -= 0.1f;
        else maxStudyTime = 1.f;
        NextScene();
    }

    void Init() override
    {
        timeRemaining = maxStudyTime;

        PersonGraphics targetGraphics = Randomiser::CreateRandomPerson();
        ChooseTargetScene::target = targetGraphics;
        targetPerson[0] = Person(Vector2{(WINDOW_W-128*3), (150)}, targetGraphics);
        // infoBox.Reset(); // We shouldn't force the player to see + hear this every time!
        infoBox.Play();

        background = LoadTexture("resources/bg_target.png");
    }

    void Tick(float deltaTime) override
    {
        UpdateMusicStream(MenuScene::mainTheme);
        if (timeRemaining <= 0.f || IsKeyPressed(KEY_SPACE) && !infoBox.isPlaying()) Done();
        
        BeginDrawing();

        DrawTexture(background, 0, 0, WHITE);

        targetPerson[0].Draw();
        DrawText(TextFormat("%.1f", timeRemaining), 10, 10, 65, RED);

        if (IsKeyPressed(KEY_SPACE)) infoBox.ChangeDelay(0.002f);
        infoBox.Update();

        EndDrawing();

        timeRemaining -= deltaTime; // GetFrameTime() also accessible
        targetPerson[0].pos.y -= sinf(GetTime()) * 0.7f;
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
        bin.rect.x = WINDOW_W - bin.rect.width;
        bin.rect.y = 0;

        background = LoadTexture("resources/bg_dark.png");
    }

    inline static size_t score = 0;
    inline static PersonBinnedStatus pbs = PersonBinnedStatus::None;
private:

    Bin bin;
    Texture2D background;
    std::vector<Person> persons;
    Person *m_lastHovered = nullptr;

    float m_maxTime = 20.f;
    float m_timer = m_maxTime;

    int crowdNumber = 20;
    int targetIndex;
    void Init() override
    {
        transitioning = false; transitionAlpha = 0;
        Person::somethingGrabbed = false;
        m_timer = m_maxTime;

        // -- Generate the crowd --
        persons = createCrowd(crowdNumber);
        
        // -- Create target Person --
        // TODO: Wasteful approach, please clean up, I'm sick and tired
        // i.e. we're resetting one when we can just set it in the first place
        targetIndex = rand() % crowdNumber;
        persons[targetIndex] = Person(Vector2{(float)(75 + (rand() % 930)), (float)(150 + (rand() % 350))}, ChooseTargetScene::target, true);
    }

    bool transitioning = false; uint16_t transitionAlpha = 0;
    void Transition()
    {
        DrawRectangle(0, 0, WINDOW_W, WINDOW_H, Color { 0, 0, 0, (uint16_t)transitionAlpha });
        transitionAlpha += 4;
        if (transitionAlpha > 255) transitionAlpha |= 0xff; // Clamp to 255 when truncated
        if ((uint8_t)transitionAlpha == 255) {
            NextScene();
        }
    }

    void Tick(float deltaTime) override
    {
        UpdateMusicStream(MenuScene::mainTheme);
        m_lastHovered = nullptr;

        // -- Our Layering Problems are Over -- (yay !!)
        for (auto &person : persons) {
            // Get topmost Person we are hovering over
            if (person.IsMouseOver()) m_lastHovered = &person;
        }

        for (auto &person : persons) {
            // Only allow drag-n-drop behaviour when topmost one!
            bool shouldSelect = m_lastHovered == &person;
            auto state = person.Update(GetTime(), shouldSelect, bin.isOpen());
            if (state != PersonBinnedStatus::None) {
                transitioning = true;
                MainScene::pbs = state;
            }
        }
        // ------------------------------------

        // if (IsKeyPressed(KEY_SPACE)){ PreviousScene(); } // Regenerate target
        if (IsKeyPressed(KEY_R)) Init(); // Regenerate crowd

        BeginDrawing();
        DrawTexture(background, 0, 0, WHITE);
        // std::cout << persons.size() << std::endl;
        bin.Draw();
        for (auto &person : persons) {
            person.Draw();
        }
        // If target in crowd, `crowdNumber - 1` please
        persons[targetIndex].DrawDebug();


        DrawText(TextFormat("%.1f", m_timer), 10, 10, 60, RED);
        // DrawFPS(20, 20);
        if (transitioning) {
            Transition();
        }

        EndDrawing();

        // Timer things
        if (transitioning) return;
        m_timer -= deltaTime;
        if (m_timer <= 0.f) { pbs = PersonBinnedStatus::ROOT; NextScene();}
    }

    std::vector<Person> createCrowd(int amount){
        std::vector<Person> persons;

        for (int i = 0; i < amount; i++) {         
            persons.push_back(Person(Vector2{(float)(75 + (rand() % (WINDOW_W-200))), (float)(150 + (rand() % (WINDOW_H-200)))}));
        }
        
        return persons;
    }
};

class ResultsScene : public Scene
{
public:
    ResultsScene(SceneManager *sm) : Scene(sm), resultsBox(0.04f, 200, 200)
    {
        resultsBox.SetColour(WHITE);
        resultsBox.SetSecondaryColour(GRAY);
    }
private:
    inline static std::string positiveMessages[10] = {
        "A job well done, doctor.",
        "Splendid work... I'm pleased!",
        "Begone, rotten memory...",
        "I don't remember a thing!",
        "Great stuff.",
        "A technological feat!",
        "That tickled!",
        "Doctor, have you seen Men In Black?",
        "I've got about 21 more on my list.",
        "What did I eat for breakfast again?",
    };

    inline static std::string negativeMessages[10] = {
        "Technological malfunction.",
        "Instead, doctor, YOU'VE forgotten...",
        "I remember it all... and I like it?",
        "Doctor, I'm having second thoughts.",
        "What has this world come to?",
        "Fuelling a dystopia.",
        "Doctor, I think that was my friend.",
        "Lest we forget.",
        "Doctor, I've overestimated you!",
        "Something's wrong; I still hate them.",
    };

    inline static std::string ranOutOfTImeMessages[1]{
        "fuck you"
    };

    TextBox resultsBox;
    void Init() override
    {
        if (MainScene::pbs == PersonBinnedStatus::BinnedTarget)
            MainScene::score++;

        // const char *msg =
        //     MainScene::pbs == PersonBinnedStatus::BinnedTarget ?
        //     positiveMessages[rand() % 10].c_str()
        //     : negativeMessages[rand() % 10].c_str();
        
        const char *msg;       

        if (MainScene::pbs == PersonBinnedStatus::BinnedTarget)
        {
            msg = positiveMessages[rand() % 10].c_str();
        }else if (MainScene::pbs == PersonBinnedStatus::BinnedWrong){
            msg = negativeMessages[rand() % 10].c_str();
        }else{
            msg = ranOutOfTImeMessages[0].c_str();
        }

        std::string fullMsg = std::string(msg) + "\n \nScore " + std::to_string(MainScene::score);
        resultsBox.SetText(std::string_view{fullMsg});
        resultsBox.ChangeDelay(0.04f);
        resultsBox.Reposition(WINDOW_W/2-MeasureText(msg, TEXTBOX_FONT_SIZE)/2, 200);
        resultsBox.Reset();
        resultsBox.Play();
    }

    void Tick(float deltaTime) override
    {
        UpdateMusicStream(MenuScene::mainTheme);
        if (MainScene::pbs == PersonBinnedStatus::ROOT) SwitchScene(5);
        if (IsKeyPressed(KEY_SPACE) && !resultsBox.isPlaying()) SwitchScene(2);
        BeginDrawing();
        ClearBackground(BLACK);
        resultsBox.Update();
        if (IsKeyPressed(KEY_SPACE)) resultsBox.ChangeDelay(0.005f);
        EndDrawing();
    }
};


class GameOverScene : public Scene
{
    TextBox tb;
public:
    // Initializing members only once, ever
    GameOverScene(SceneManager *sm)
        : Scene(sm),
          tb(0.04f, 200, 200)
    {tb.SetText(std::string_view{"Game Over"});}
    void Init() override
    {
        tb.Reset();
        tb.Play();
        
    }
    
    void Tick(float deltaTime) override
    {
        UpdateMusicStream(MenuScene::mainTheme);
        if (IsKeyPressed(KEY_SPACE)) {
            SwitchScene(1);
        }
        BeginDrawing();
        ClearBackground(WHITE);
        tb.Update();
        EndDrawing();
    }
};
