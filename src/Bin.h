#pragma once
#include "raylib.h"

class Bin
{
 private:
    Texture2D m_textures[2];
    Texture2D m_texture;
    bool m_opened = false;
 public:
    Rectangle rect;

    Bin(Texture2D textureOpen, Texture2D textureClosed);
    void Draw();
    void Open();
    void Close();
    bool isOpen();
};
