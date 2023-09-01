#pragma once
#include "raylib.h"
#include <string>
#include <string_view>

class TextBox
{
 private:
    const Sound m_charSound;

    std::string m_fullText;
    bool m_playing = false;
    size_t m_index = 0;

    float m_charDelay;
    float m_lastTime = 0.f;

    void DrawNext();
 public:
    TextBox(float charDelay, Sound charSound);
    void SetText(const std::string_view text);
    void Play();
    void Stop();
    void Reset();
    void Update();
};
