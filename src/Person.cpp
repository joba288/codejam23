#include "./Person.h"

bool Person::somethingGrabbed = false;

Person::Person(Vector2 _pos, Texture2D head, Texture2D hair, Texture2D eye, Texture2D nose, Texture2D mouth, Texture2D shirt, Texture2D hand, Texture2D foot, Color cShirt, Color cHair, Color cSkin){
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

void Person::Draw(){
    //shirt
    DrawTextureEx(shirtTex, Vector2{pos.x - (shirtTex.width/2 * scale) , pos.y - ((shirtTex.height/2 - 100.f)* scale) }, rotation, scale, shirtColor);
    //draw head
    DrawTextureEx(headTex, Vector2{pos.x - (headTex.width/2 * scale), pos.y - ((headTex.height/2 - 2.5f)* scale)}, rotation, scale, skinColor);
    //draw mouth
    DrawTextureEx(mouthTex, Vector2{pos.x - (mouthTex.width/2) * scale, pos.y - (mouthTex.height/2 - 40.f)* scale}, rotation, scale, skinColor);
    //nose
    DrawTextureEx(noseTex, Vector2{pos.x - (noseTex.width/2) * scale, pos.y - (noseTex.height/2 - 5.f)* scale}, rotation, scale, skinColor);
    //eyes
    DrawTextureEx(eyeTex, Vector2{pos.x - (eyeTex.width/2) * scale, pos.y - (eyeTex.height/2 + 25.f)* scale}, rotation, scale, WHITE);
    //hair
    DrawTextureEx(hairTex, Vector2{pos.x - (hairTex.width/2) * scale, pos.y - (eyeTex.height/2 + 65.f)* scale}, rotation, scale, hairColor);
    //hand
        
    //foot
    
    //DrawRectangleLines(pos.x - 50, pos.y - 75, 100, 200, SKYBLUE);
        
}
void Person::Update(float time) {
    //update collision rectangle
    collRec.x = pos.x - collRec.width/2;
    collRec.y = pos.y - collRec.height/2;
    Vector2 mouse = GetMousePosition();
    //drag and drop code
    if (grabbed){          
        pos.x = mouse.x - grabbedOffset.x;
        pos.y = mouse.y - grabbedOffset.y;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            grabbed = false;
            Person::somethingGrabbed = false;
        }
    }else{
        
        if(CheckCollisionPointRec(mouse, collRec)){ //if mouse is inside object pick up
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !Person::somethingGrabbed){
                grabbed = true;
                Person::somethingGrabbed = true;
                grabbedOffset = {mouse.x - pos.x, mouse.y - pos.y}; // this is so that the object is in the same pos relative to the mouse when grabbed
                
            }
            scale += 0.15*(0.9 - scale);//lerp to .9 when hovering over
        }else{
            scale += 0.15*(1 - scale);//lerp back to 1 when not
        }
    }
    
}   
