#pragma once
#include "raylib.h"
#include "./Scene.h"
#include "./TextBox.h"

class OpeningScene : public Scene
{
    TextBox box;
    int showIndex = 0;

    const Texture2D bgs[4];

    inline static const std::string msgs[4] = {

            "Once, there was a happy land\n"
            "known as the Jiiverse.\n \n"
            "All who lived on this land were\n"
            "at peace with one another.",

            "However, in the year 20XX,\n"
            "questionable technological and\n"
            "political developments sparked\n"
            "a era of disagreement for\n"
            "the poor Jiis...",

            "Thus, the new dystopian future\n"
            "was realised in what used to\n"
            "be the simple, happy Jiiverse.\n \n"
            "Everyone was upset with\n"
            "everyone else.",

            "Now, the doctors of today set\n"
            "out to fulfil the desperate\n"
            "plans of the Jiis to forget\n"
            "each other... and unbeknownst\n"
            "to anyone, the new tech may\n"
            "easily malfunction."
    };
    size_t msgIndex = 0;

    void IncrementText()
    {
        if (!(msgIndex < 4-1)) { // Hard-coded size minus one
            NextScene();
            return;
        }
        box.Reset();
        box.ChangeDelay(0.06f); // Not necessary EVERY time but I have 3h left
        box.SetText(std::string_view{ msgs[++msgIndex] });
        box.Play();
    }

    void Init() override
    {
        box.Reset();
        box.SetText(std::string_view{ msgs[msgIndex] });
        box.Play();
    }

    static constexpr float maxMsgTimer = 2.0f;
    float msgTimer = maxMsgTimer;
    void Tick(float deltaTime) override
    {
        BeginDrawing();
        DrawTexture(bgs[msgIndex], 0, 0, WHITE);

        if (IsKeyPressed(KEY_SPACE)) {
            if (box.isPlaying()) box.ChangeDelay(0.001f);
            else IncrementText();
        };

        
        box.Update();
        
        EndDrawing();
        
        if (msgTimer <= 0.f) {
            IncrementText();
            msgTimer = maxMsgTimer;
        }
        if (!box.isPlaying()) msgTimer -= GetFrameTime();
    }

public:
    OpeningScene(SceneManager *sm)
        : Scene(sm), box(0.06f, 50, 30),
          bgs {
              LoadTexture("resources/bg_intro_1.png"),
              LoadTexture("resources/bg_intro_2.png"),
              LoadTexture("resources/bg_intro_3.png"),
              LoadTexture("resources/bg_intro_4.png"),
          }
    {
    }
};
