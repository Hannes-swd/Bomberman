#include "textures.h"
#include <iostream>

std::unordered_map<std::string, Texture2D> textures;

void loadTextures() {
    textures["player"] = LoadTexture("img/player.png");
    
    //fehlerüberprüffung
    for (auto& pair : textures) {
        if (pair.second.id == 0) {
            std::cout << "Fehler beim Laden: " << pair.first << std::endl;
        }
    }
}

void unloadTextures() {
    for (auto& pair : textures) {
        UnloadTexture(pair.second);
    }
    textures.clear();
}