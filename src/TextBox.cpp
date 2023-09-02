#include "./TextBox.h"
#include "./SoundManager.h"

TextBox::TextBox(float charDelay) : m_fullText(std::string_view("This is a test of epic proportions"))
{
    m_charDelay = charDelay;
}

void TextBox::SetText(const std::string_view text)
{
    m_fullText = text;
}

void TextBox::Play() { m_playing = true; }
void TextBox::Stop() { m_playing = false; }
void TextBox::Reset() { m_index = 0; }
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
        }
    }
    DrawText(
             m_fullText.substr(0, m_index).c_str(),
             100, 100, 50, BLUE
             );
    if (m_index == m_fullText.length()) Stop();
}
