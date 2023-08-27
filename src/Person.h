#include "raylib.h"

class Person{
    public:

        Vector2 pos;
        Texture2D headTex, hairTex, eyeTex, noseTex, mouthTex, shirtTex, handTex, footTex;
        Color hairColor, shirtColor, skinColor;

        float scale = 1.f;
        



        Person(Vector2 _pos, Texture2D head, Texture2D hair, Texture2D eye, Texture2D nose, Texture2D mouth, Texture2D shirt, Texture2D hand, Texture2D foot, Color cShirt, Color cHair, Color cSkin){
            pos = _pos;
            headTex = head;
            hairTex = hair;
            eyeTex = eye;
            noseTex = nose;
            mouthTex = mouth;
            handTex = hand;
            footTex = foot;
            shirtTex = shirt;

            hairColor = cHair;
            shirtColor = cShirt;
            skinColor = cSkin;

        }

        void Draw(){
            //shirt
            DrawTextureEx(shirtTex, Vector2{pos.x - (shirtTex.width/2 * scale) , pos.y - ((shirtTex.height/2 - 100.f)* scale) }, 0.f, scale, shirtColor);
            //draw head
            DrawTextureEx(headTex, Vector2{pos.x - (headTex.width/2 * scale), pos.y - ((headTex.height/2 - 2.5f)* scale)}, 0.f, scale, skinColor);
            //draw mouth
            DrawTextureEx(mouthTex, Vector2{pos.x - (mouthTex.width/2) * scale, pos.y - (mouthTex.height/2 - 40.f)* scale}, 0.f, scale, skinColor);
            //nose
            DrawTextureEx(noseTex, Vector2{pos.x - (noseTex.width/2) * scale, pos.y - (noseTex.height/2 - 5.f)* scale}, 0.f, scale, skinColor);
            //eyes
            DrawTextureEx(eyeTex, Vector2{pos.x - (eyeTex.width/2) * scale, pos.y - (eyeTex.height/2 + 25.f)* scale}, 0.f, scale, WHITE);
            //hair
            DrawTextureEx(hairTex, Vector2{pos.x - (hairTex.width/2) * scale, pos.y - (eyeTex.height/2 + 65.f)* scale}, 0.f, scale, hairColor);

            //hand
            
            //foot
            
        }

        void Update(){


        }


};