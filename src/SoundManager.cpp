#include "./SoundManager.h"

std::unordered_map<std::string_view, Sound> SoundManager::sounds;

bool SoundManager::Load(std::string_view fileName)
{
    std::string fullName =
        std::string("resources/sounds/") +
        std::string(fileName);

    Sound s = LoadSound(fullName.c_str());
    if (!IsSoundReady(s)) {
        std::cerr << "ERROR: Sound `" << fullName << "` failed to load Check Raylib logs!" << std::endl;
        return false;
    }
    SoundManager::sounds[fileName] = s;
    // SoundManager::Play(fileName);
    std::cout << "SOUNDMANAGER: Loaded sound `" << fullName << "` a-succesfoolay." << std::endl;
    return true;
}

// First time using optionals... I might as well check for NULL/nullptr
// But this makes me look cool, so that's the only reason I'm using it
// So maybe TODO: make this actually meaningfull, dumbass.
// To Dorbell, Love, Dorbell
std::optional<Sound*> SoundManager::Get(std::string_view fileName)
{
    if (SoundManager::sounds.find(fileName) == SoundManager::sounds.end()) return {};

    // std::cout << "Got Sound " << fileName << std::endl;
    return std::make_optional<Sound*>(&SoundManager::sounds[fileName]);
}

void SoundManager::Play(std::string_view fileName)
{
    auto sound = SoundManager::Get(fileName);
    if (!sound.has_value()) {
        std::cerr << "ERROR: Sound `" << fileName << "` not found interally." << std::endl;
        return;
    }

    PlaySound(*sound.value());
}
