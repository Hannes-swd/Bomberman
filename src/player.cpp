#include "player.h" // include playerclass from player.h
#include "raylib.h"
#include "bomb.h"
#include "player.h"
#include "textures.h"

Player::Player(int x, int y) : HP(10), speed(0), positionX(x), positionY(y), bombSetter(0) {} // define player

// functions
// set bomb
void Player::setBomb() {
    if (bombSetter != 0) {
        if (GetTime() - bombSetter >= 5.0){
            bombSetter = 0;
        }
        return;
    }

    placeBomb(positionX, positionY);
    bombSetter = GetTime();
}

// move up
void Player::moveUp() {
    if(checkGround(positionX, positionY)) {
        positionY -= 1.5;
    }
}

// move Down
void Player::moveDown() {
    positionY += 1.5;
}

// move left
void Player::moveLeft() {
    positionX -= 1.5;
}

// move right
void Player::moveRight() {
    positionX += 1.5;
}

void Player::drawPlayer(PlayerType type) {
    if (type == PLAYER_ONE) {
        float scale = 32.0f / textures["player1"].width;
        float drawX = (float)positionX - (textures["player1"].width * scale) / 2.0f;
        float drawY = (float)positionY - (textures["player1"].height * scale) / 2.0f;
        DrawTextureEx(textures["player1"], { drawX, drawY }, 0, scale, WHITE);
    }
    if (type == PLAYER_TWO) {
        float scale = 32.0f / textures["player2"].width;
        float drawX = (float)positionX - (textures["player2"].width * scale) / 2.0f;
        float drawY = (float)positionY - (textures["player2"].height * scale) / 2.0f;
        DrawTextureEx(textures["player2"], { drawX, drawY }, 0, scale, WHITE);
    }
}

void Player::setplayer(int x, int y) {
    positionX = x;
    positionY = y;
}
int Player::getPlayerLive() const {
    return HP;
}

bool Player::checkGround(double x, double y){
    int GridX = (int)(x / 32);
    int GridY = (int)(y / 32);

    if (currentMap.data[GridY][GridX] != TILE_FLOOR) {
        return false;
    } else {
        return true;
    }
}

void playermoovment(Player& player1, Player& player2) {
    if(IsKeyDown(KEY_W))
        player1.moveUp();

    if (IsKeyDown(KEY_S))
        player1.moveDown();

    if (IsKeyDown(KEY_A))
        player1.moveLeft();

    if (IsKeyDown(KEY_D))
        player1.moveRight();

    if (IsKeyDown(KEY_UP))
        player2.moveUp();

    if (IsKeyDown(KEY_DOWN))
        player2.moveDown();

    if (IsKeyDown(KEY_LEFT))
        player2.moveLeft();

    if (IsKeyDown(KEY_RIGHT))
        player2.moveRight();

    if (IsKeyPressed(KEY_TAB))
        player1.setBomb();

    if (IsKeyPressed(KEY_RIGHT_SHIFT))
    {
        player2.setBomb();
    }
}