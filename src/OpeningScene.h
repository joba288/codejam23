#pragma once
#include "raylib.h"
#include "./Scene.h"
#include "./TextBox.h"

class OpeningScene : public Scene
{
    TextBox box;
    int showIndex = 0;
    void Init() override
    {
        box.SetText(std::string_view{ "ONCE UPON A TIME.....THERE WAS\nA HAPPY LAND KNOWN AS THE\nJIIVERSE." });
        box.Play();
    }

    void Tick(float deltaTime) override
    {
        BeginDrawing();
        ClearBackground(WHITE);

        if (IsKeyPressed(KEY_SPACE)) NextScene();

        box.Update();
        EndDrawing();
    }

public:
    OpeningScene(SceneManager *sm) : Scene(sm), box(0.05f, 100, 100) {}
};
