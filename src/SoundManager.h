#pragma once
#include "raylib.h"
#include <iostream>
#include <vector>
#include <optional>
#include <string_view>
#include <unordered_map>

class SoundManager
{
private:
    static std::unordered_map<std::string_view, Sound> sounds;
public:
    static bool Load(std::string_view fileName); // e.g. "shid.mp3"
    static void Play(std::string_view fileName);
    static std::optional<Sound*> Get(std::string_view fileName);
};
