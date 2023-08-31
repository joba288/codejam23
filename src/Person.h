#pragma once // PLEASE Joba!!

#include "raylib.h"
#include "./Randomiser.h"
#include <cmath>
#include <iostream>

class Person {
private:
        
public:

    Vector2 pos;
    Texture2D headTex, hairTex, eyeTex, noseTex, mouthTex, shirtTex, handTex, footTex;
    Color hairColor, shirtColor, skinColor;

    PersonGraphics graphics;

    float scale = 1.0f;
    float rotation = 0.f;

    Rectangle collRec = Rectangle{pos.x, pos.y, 100.f, 225.f};

    bool grabbed = false;
    Vector2 grabbedOffset;
        
    static bool somethingGrabbed;
    bool IsMouseOver();
        
    Person(Vector2 _pos); // Random
    Person(Vector2 _pos, PersonGraphics fixed); // Fixed

    void Draw();
    void Update(float time, bool hovering);
};
