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

void setplayer(int x , int y) {

}