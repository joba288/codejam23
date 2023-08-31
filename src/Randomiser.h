#pragma once

#include "raylib.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <array>

struct PersonGraphics
{
    Texture2D headTex;
    Texture2D hairTex;
    Texture2D eyeTex;
    Texture2D noseTex;
    Texture2D mouthTex;
    Texture2D shirtTex;
    Texture2D handTex;
    Texture2D footTex;
    Color hairColor, shirtColor, skinColor;
};

class Randomiser
{
private:
    static std::vector<Texture2D> hairArray;
    static std::vector<Texture2D> headArray;
    static std::vector<Texture2D> eyesArray;
    static std::vector<Texture2D> noseArray;
    static std::vector<Texture2D> mouthArray;
    static std::vector<Texture2D> bodyArray;
    static std::vector<Texture2D> handArray;
    static std::vector<Texture2D> footArray;

    static std::vector<Color> cHairArray;
    static std::vector<Color> cSkinArray;

    void LoadTextures();
public:
    static PersonGraphics CreateRandomPerson();
    Randomiser();
};
