#include "player.h" // include playerclass from player.h
#include "raylib.h"
#include "bomb.h"
#include "player.h"
#include "textures.h"
#include "wall.h"

Player::Player(int x, int y) : HP(10), 
speed(0), 
positionX(x), 
positionY(y), 
bombSetter(0), 
bombRange(1), 
lastDamageTime(0), 
bombcount(1),
wallCount(1),
facingX(0),
facingY(0)
{}

void Player::takeDamage(int amount) {
    if (GetTime() - lastDamageTime < 3.0) return; // Cooldown
    HP -= amount;
    lastDamageTime = GetTime();
}

void Player::setBomb() {
    int activeBombs = 0;
    double now = GetTime();
    
    for (const auto& bomb : BombList) {
        if (now - bomb.spawnTime < 3.0) {
            activeBombs++;
        }
    }
    if (activeBombs < bombcount) {
        placeBomb(positionX, positionY, bombRange);
    }
}

void Player::setWall() {
    int activeWalls = 0;

    if (activeWalls < wallCount) {
        drawWall(positionX + facingX * 32, positionY + facingY * 32);
        activeWalls++;
    }
}

// move up
void Player::moveUp() {
    if(checkGround(positionX, positionY - 1.5)) {
        positionY -= 1.5;
        facingY = 1;
        facingX = 0;
    }
}

// move Down
void Player::moveDown() {
    if(checkGround(positionX, positionY + 1.5)) {
        positionY += 1.5;
        facingY = 1;
        facingX = 0;
    }
}

// move left
void Player::moveLeft() {
    if(checkGround(positionX - 1.5, positionY)) {
        positionX -= 1.5;
        facingY = 0;
        facingX =  1;
    }
}

// move right
void Player::moveRight() {
    if(checkGround(positionX + 1.5, positionY)) {
        positionX += 1.5;
        facingY = 0;
        facingX = 1;
    }
}

void Player::drawPlayer(PlayerType type) {
    if (type == PLAYER_ONE) {
        float scale = 16.0f / textures["player1"].width;
        float drawX = (float)positionX - (textures["player1"].width * scale) / 2.0f;
        float drawY = (float)positionY - (textures["player1"].height * scale) / 2.0f;
        DrawTextureEx(textures["player1"], { drawX, drawY }, 0, scale, WHITE);
    }
    if (type == PLAYER_TWO) {
        float scale = 16.0f / textures["player2"].width;
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

// int Player::getBombCount() const {
//    return bombcount;
// }

bool Player::checkGround(double x, double y) {
    int margin = 14; 
    
    // check ALL corner
    int corners[4][2] = {
        { (int)(x - margin) / 32, (int)(y - margin) / 32 }, // left up
        { (int)(x + margin) / 32, (int)(y - margin) / 32 }, // right up
        { (int)(x - margin) / 32, (int)(y + margin) / 32 }, // left down
        { (int)(x + margin) / 32, (int)(y + margin) / 32 }, // right down
    };

    for (auto& c : corners) {
        if (c[1] < 0 || c[0] < 0) return false; // corner check
        if (currentMap.data[c[1]][c[0]] != TILE_FLOOR) return false; // floor check
    }
    return true;
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

    if (IsKeyDown(KEY_I))
        player2.moveUp();

    if (IsKeyDown(KEY_K))
        player2.moveDown();

    if (IsKeyDown(KEY_J))
        player2.moveLeft();

    if (IsKeyDown(KEY_L))
        player2.moveRight();

    if (IsKeyPressed(KEY_Q))
        player1.setBomb();

    if (IsKeyPressed(KEY_U))
    {
        player2.setBomb();
    }

    if (IsKeyPressed(KEY_TAB))
    {
        player1.setWall();
    }

    if (IsKeyPressed(KEY_Y))
    {
        player2.setWall();
    }

    if (isPlayerInExplosion(player1.getPositionX(), player1.getPositionY()))
        player1.takeDamage(2);

    if (isPlayerInExplosion(player2.getPositionX(), player2.getPositionY()))
        player2.takeDamage(2);
}

void Player::addBombRange() {
    bombRange++;
}

void Player::addBombCounte() {
    bombcount++;
}