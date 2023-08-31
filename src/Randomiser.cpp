#include "./Randomiser.h"

std::vector<Texture2D> Randomiser::hairArray;
std::vector<Texture2D> Randomiser::headArray;
std::vector<Texture2D> Randomiser::eyesArray;
std::vector<Texture2D> Randomiser::noseArray;
std::vector<Texture2D> Randomiser::mouthArray;
std::vector<Texture2D> Randomiser::bodyArray;
std::vector<Texture2D> Randomiser::handArray;
std::vector<Texture2D> Randomiser::footArray;
std::vector<Color> Randomiser::cHairArray;
std::vector<Color> Randomiser::cSkinArray;

Randomiser::Randomiser()
{
    LoadTextures();
}

void Randomiser::LoadTextures()
{
    Randomiser::hairArray.push_back(LoadTexture("resources/hair1.png"));
    Randomiser::hairArray.push_back(LoadTexture("resources/hair2.png"));
    Randomiser::headArray.push_back(LoadTexture("resources/head1.png"));
    Randomiser::eyesArray.push_back(LoadTexture("resources/eyes1.png"));
    Randomiser::eyesArray.push_back(LoadTexture("resources/eyes2.png"));
    Randomiser::noseArray.push_back(LoadTexture("resources/nose1.png"));
    Randomiser::noseArray.push_back(LoadTexture("resources/nose2.png"));
    Randomiser::mouthArray.push_back(LoadTexture("resources/mouth1.png"));
    Randomiser::bodyArray.push_back(LoadTexture("resources/body1.png"));

    Randomiser::handArray.push_back(LoadTexture("resources/hand1.png"));
    Randomiser::footArray.push_back(LoadTexture("resources/foot1.png"));

    Randomiser::cHairArray.push_back(BROWN); // will make a palette later, these
    Randomiser::cHairArray.push_back(BLACK); // colours are just temporary
    Randomiser::cHairArray.push_back(YELLOW);
    Randomiser::cHairArray.push_back(ORANGE);
    
    Randomiser::cSkinArray.push_back(PINK);
    Randomiser::cSkinArray.push_back(BROWN);
    Randomiser::cSkinArray.push_back(RAYWHITE);
}

Person Randomiser::createRandomPerson(int seed, Vector2 pos)
{
    srand(seed);
    return Person(
        pos,
        headArray[rand() % headArray.size()], hairArray[rand() % hairArray.size()],
        eyesArray[rand() % eyesArray.size()], noseArray[rand() % noseArray.size()],
        mouthArray[rand() % mouthArray.size()], bodyArray[rand() % bodyArray.size()],
        handArray[rand() % handArray.size()], footArray[rand() % footArray.size()],
        (Color){ rand() % 255, rand() % 255, rand() % 255, 255 },
        cHairArray[rand() % cHairArray.size()],
        cSkinArray[rand() % cSkinArray.size()]
        );
}