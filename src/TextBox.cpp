#include "./TextBox.h"
#include "./SoundManager.h"

#include <sstream>
#include <string>

TextBox::TextBox(float charDelay, int x, int y)
{
    m_colour = RED;
    m_colour2 = BLACK;
    m_charDelay = charDelay;
    m_lines.push_back(std::string("Forget Jii Not"));
    m_position[0] = x;
    m_position[1] = y;
}

void TextBox::SplitText(std::string_view raw)
{
    // If this works, then I just unintentionally  understood std::move
    std::stringstream stream(std::move(std::string(raw)));
    std::string to;

    while (std::getline(stream, to)) {
        m_lines.push_back(to);
    }
    // for (auto &i : m_lines) std::cout << i << std::endl;
}

void TextBox::SetText(const std::string_view text)
{
    m_lines.erase(m_lines.begin(), m_lines.end()); m_lines.clear();
    this->Reset();
    m_fullText = text;
    SplitText(text);
}

void TextBox::ChangeDelay(float newDelay)
{
    m_charDelay = newDelay;
}

void TextBox::Reposition(int x, int y)
{
    m_position[0] = x;
    m_position[1] = y;
}

void TextBox::SetColour(Color colour)
{
    m_colour = colour;
}

void TextBox::SetSecondaryColour(Color colour)
{
    m_colour2 = colour;
}

void TextBox::Play() { m_playing = true; }
void TextBox::Stop() { m_playing = false; }
void TextBox::Reset() { m_line = 0; m_index = 0; }
void TextBox::Update()
{
    DrawNext();
}

void TextBox::DrawNext()
{
    if (m_playing) {
        if (GetTime() >= m_lastTime + m_charDelay) {
            if (m_playing) {
                SoundManager::Play("char.wav");
            }
            m_index++; m_lastTime = GetTime();
            if (m_index == m_lines[m_line].length()) {
                m_line++; m_index = 0;
            }
        }
    }
    for (size_t i = 0; i < m_lines.size(); i++) {
        const std::string &line = m_lines.at(i);
        if (m_line < i) continue;
        DrawText(
                 line.substr(0,
                             i == m_line ? m_index : line.length()
                             ).c_str(),
                 m_position[0] + 3, m_position[1] + 3 + 50 * i, TEXTBOX_FONT_SIZE, m_colour2
                 );
        DrawText(
                 line.substr(0,
                             i == m_line ? m_index : line.length()
                             ).c_str(),
                 m_position[0], m_position[1] + 50 * i, TEXTBOX_FONT_SIZE, m_colour
                 );
    }
    if (m_line == m_lines.size()) Stop();
}

bool TextBox::isPlaying() { return m_playing; }
