#include "./Person.h"


// -------------------------------------------------------------------------------
// Globals
// -------------------------------------------------------------------------------

bool Person::somethingGrabbed = false;

Shader Person::dissolveShader;
int Person::dissolveTimeLoc;

// -------------------------------------------------------------------------------

Person::Person(Vector2 _pos)
{
    pos = _pos;
    this->graphics = Randomiser::CreateRandomPerson();
}

Person::Person(Vector2 _pos, PersonGraphics fixed)
{
    pos = _pos;
    this->graphics = fixed;
}


void Person::Draw(){

    if (beingDestroyed)
    {       
        BeginShaderMode(Person::dissolveShader);
        dissolveTime += 0.01f;
        SetShaderValue(Person::dissolveShader, Person::dissolveTimeLoc, &(dissolveTime), SHADER_UNIFORM_FLOAT); 
    }

    
    DrawTextureEx(graphics.shirtTex, Vector2{pos.x - (graphics.shirtTex.width/2 * scale) , pos.y - ((graphics.shirtTex.height/2 - 100.f)* scale) }, rotation, scale, graphics.shirtColor);
    DrawTextureEx(graphics.headTex, Vector2{pos.x - (graphics.headTex.width/2 * scale), pos.y - ((graphics.headTex.height/2 - 2.5f)* scale)}, rotation, scale, graphics.skinColor);
    DrawTextureEx(graphics.mouthTex, Vector2{pos.x - (graphics.mouthTex.width/2) * scale, pos.y - (graphics.mouthTex.height/2 - 40.f)* scale}, rotation, scale, graphics.skinColor);
    DrawTextureEx(graphics.noseTex, Vector2{pos.x - (graphics.noseTex.width/2) * scale, pos.y - (graphics.noseTex.height/2 - 5.f)* scale}, rotation, scale, graphics.skinColor);
    DrawTextureEx(graphics.eyeTex, Vector2{pos.x - (graphics.eyeTex.width/2) * scale, pos.y - (graphics.eyeTex.height/2 + 25.f)* scale}, rotation, scale, WHITE);
    DrawTextureEx(graphics.hairTex, Vector2{pos.x - (graphics.hairTex.width/2) * scale, pos.y - (graphics.eyeTex.height/2 + 65.f)* scale}, rotation, scale, graphics.hairColor);

    EndShaderMode();
}

void Person::DrawDebug()
{
    DrawRectangleLinesEx(collRec, 8.f, GREEN);
}

bool Person::IsMouseOver()
{
    return CheckCollisionPointRec(GetMousePosition(), collRec);
}

void Person::Update(float time, bool hovering) {

    // Update collision rectangle
    collRec.x = pos.x - collRec.width/2;
    collRec.y = pos.y - collRec.height/3;

    // ------------------------------------
    // Refactored the function a little bit
    // TODO: Return and clean up rest later
    // ------------------------------------
    scale += 0.15f * (1.f - (0.1f * (float)hovering) - scale);

    if (!hovering && !Person::somethingGrabbed) return;
    Vector2 mouse = GetMousePosition();
    // ------------------------------------
    
    //drag and drop code
    if (grabbed)
    {          
        pos.x = mouse.x - grabbedOffset.x;
        pos.y = mouse.y - grabbedOffset.y;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            grabbed = false;
            Person::somethingGrabbed = false;
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && !beingDestroyed)
        {
            beingDestroyed = true;
        }
    }else{
        
        if(hovering)
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !Person::somethingGrabbed)
            {
                grabbed = true;
                Person::somethingGrabbed = true;
                grabbedOffset = {mouse.x - pos.x, mouse.y - pos.y}; // this is so that the object is in the same pos relative to the mouse when grabbed
                
            }
        }
    }

    
}   
