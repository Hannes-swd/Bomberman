#pragma once
#include "raylib.h"
#include <unordered_map>
#include <string>

extern std::unordered_map<std::string, Texture2D> textures;

void loadTextures();
void unloadTextures();