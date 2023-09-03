#pragma once // PLEASE Joba!!

#include "raylib.h"
#include "./Randomiser.h"
#include <cmath>
#include <iostream>

enum class PersonBinnedStatus {
    None,
    BinnedWrong,
    BinnedTarget,
};


class Person {
private:
    
public:

    Vector2 pos;
    Texture2D headTex, hairTex, eyeTex, noseTex, mouthTex, shirtTex, handTex, footTex;
    Color hairColor, shirtColor, skinColor;

    PersonGraphics graphics;

    float scale = 1.0f;
    float rotation = 0.f;
    bool isTarget = false;

    Rectangle collRec = Rectangle{pos.x, pos.y, 100.f, 225.f};

    bool grabbed = false;
    Vector2 grabbedOffset;

    bool beingDestroyed = false;

    static Shader dissolveShader;
    static int dissolveTimeLoc;
    float dissolveTime = 0.4f;

    static bool somethingGrabbed;
    bool IsMouseOver();
        
    Person(Vector2 _pos); // Random
    Person(Vector2 _pos, PersonGraphics fixed, bool target = false); // Fixed

    void Draw();
    void DrawDebug();
    PersonBinnedStatus Update(float time, bool hovering, bool binned);
};
