#include "textures.h"
#include <iostream>

std::unordered_map<std::string, Texture2D> textures;

void loadTextures() {
    textures["player1"] = LoadTexture("img/player1.png");
    textures["player2"] = LoadTexture("img/player2.png");
    textures["bomb"] = LoadTexture("img/bomb.png");
    textures["bedrock"] = LoadTexture("img/bedrock.png");
    textures["stone"] = LoadTexture("img/stone.png");
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