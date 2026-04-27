#include "textures.h"
#include <iostream>

std::unordered_map<std::string, Texture2D> textures;

void loadTextures() {
    textures["player1"] = LoadTexture("img/player1.png");
    textures["player2"] = LoadTexture("img/player2.png");
    textures["player1win"] = LoadTexture("img/player1win.png");
    textures["player2win"] = LoadTexture("img/player2win.png");
    textures["bomb"] = LoadTexture("img/bomb.png");
    textures["bedrock"] = LoadTexture("img/bedrock.png");
    textures["stone"] = LoadTexture("img/stone.png");
    textures["BombUpgrade"] = LoadTexture("img/BombUpgrade.png");
    textures["BpombCount"] = LoadTexture("img/BpombCount.png");
    textures["remotebombdetonator"] = LoadTexture("img/remotebombdetonator.png");
    textures["remotebomb"] = LoadTexture("img/remotebomb.png");
    textures["HealingPotion"] = LoadTexture("img/HealingPotion.png");
    textures["gost"] = LoadTexture("img/gost.png");

    //remotebomb

    textures["mine"] = LoadTexture("img/mine.png");
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