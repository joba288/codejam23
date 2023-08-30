#pragma once

#include "raylib.h"
#include <cmath>
#include <iostream>
#include <vector>

#include "Person.h"

class Randomiser
{
    private:


    public:

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

        Randomiser();
        void LoadTextures();
        Person createRandomPerson(int seed, Vector2 pos);



};