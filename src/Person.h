#pragma once // PLEASE Joba!!

#include "raylib.h"
#include <cmath>
#include <iostream>

class Person {
    private:
        
    public:

        Vector2 pos;
        Texture2D headTex, hairTex, eyeTex, noseTex, mouthTex, shirtTex, handTex, footTex;
        Color hairColor, shirtColor, skinColor;

        float scale = 1.0f;
        float rotation = 0.f;

        Rectangle collRec = Rectangle{pos.x, pos.y, 100.f, 225.f};

        bool grabbed = false;
        Vector2 grabbedOffset;
        
        static bool somethingGrabbed;
        bool IsMouseOver();


        
        Person(Vector2 _pos, Texture2D head, Texture2D hair, Texture2D eye, Texture2D nose, Texture2D mouth, Texture2D shirt, Texture2D hand, Texture2D foot, Color cShirt, Color cHair, Color cSkin);

        void Draw();
    void Update(float time, bool hovering);
 
        


};


