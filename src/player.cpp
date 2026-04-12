#include "player.h" // include playerclass from player.h
#include "raylib.h"
#include "bomb.h"

Player::Player(int x, int y) : HP(10), speed(0), positionX(x), positionY(y) {} // define player

// functions
// set bomb
void Player::setBomb() {
    placeBomb(positionX, positionY);
}

// move up
void Player::moveUp() {
    positionY -= 10;
}

// move Down
void Player::moveDown() {
    positionY += 10;
}

// move left
void Player::moveLeft() {
    positionX -= 10;
}

// move right
void Player::moveRight() {
    positionX += 10;
}

void Player::drawPlayer(Color color) {
    DrawCircle(positionX, positionY, 10, color);
}

void Player::setplayer(int x, int y) {
    positionX = x;
    positionY = y;
}
int Player::getPlayerLive() const {
    return HP;
}

void playermoovment(Player& player1, Player& player2) {
    if(IsKeyDown(KEY_W))
                player1.moveUp();
            
            if(IsKeyDown(KEY_S))
                player1.moveDown();

            if(IsKeyDown(KEY_A))
                player1.moveLeft();
            
            if(IsKeyDown(KEY_D))
                player1.moveRight();


            if(IsKeyDown(KEY_UP))
                player2.moveUp();
            
            if(IsKeyDown(KEY_DOWN))
                player2.moveDown();

            if(IsKeyDown(KEY_LEFT))
                player2.moveLeft();
            
            if(IsKeyDown(KEY_RIGHT))
                player2.moveRight();

            if(IsKeyPressed(KEY_TAB))
                player1.setBomb();

            if(IsKeyPressed(KEY_RIGHT_SHIFT)){
                player2.setBomb();
            }
}