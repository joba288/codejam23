#include "./Bin.h"
#include <iostream>

Bin::Bin(Texture2D textureOpen, Texture2D textureClosed)
{
    rect = Rectangle { 0.f, 0.f, textureOpen.width, textureOpen.height };
    m_textures[0] = textureOpen;
    m_textures[1] = textureClosed;
}

void Bin::Draw()
{
    m_opened = CheckCollisionPointRec(GetMousePosition(), rect);
    DrawTexture(m_textures[(int)m_opened], rect.x, rect.y, WHITE);
}
