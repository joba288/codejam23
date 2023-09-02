#pragma once
#include "raylib.h"
#include <string>
#include <string_view>
#include <vector>

class TextBox
{
 private:
    int m_position[2];
    std::vector<std::string> m_lines;
    Color m_colour;
    std::string m_fullText;
    bool m_playing = false;
    size_t m_line = 0;
    size_t m_index = 0;

    float m_charDelay;
    float m_lastTime = 0.f;
    
    void SplitText(std::string_view raw);
    void DrawNext();
 public:
    TextBox(float charDelay, int x, int y);
    void SetText(const std::string_view text);
    void SetColour(Color colour);
    void Play();
    void Stop();
    void Reset();
    void Update();
};
