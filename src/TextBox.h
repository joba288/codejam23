#pragma once
#include "raylib.h"
#include <string>
#include <string_view>
#include <vector>

#define TEXTBOX_FONT_SIZE 50

class TextBox
{
 private:
    int m_position[2];
    std::vector<std::string> m_lines;
    Color m_colour;
    Color m_colour2;
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
    void Reposition(int x, int y);
    void ChangeDelay(float newDelay);
    void SetColour(Color colour);
    void SetSecondaryColour(Color colour);
    void Play();
    void Stop();
    void Reset();
    void Update();
    bool isPlaying();
};
