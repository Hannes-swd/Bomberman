#include "player.h" // include playerclass from player.h

Player::Player(int x, int y) : HP(10), speed(0), positionX(x), positionY(y) {} // define player

// functions
// set bomb
void Player::setBomb() {
    Bomb bomb(positionX, positionY);
}

// move up
void Player::moveUp() {
    positionY += 1;
}

// move Down
void Player::moveDown() {
    positionY -= 1;
}

// move left
void Player::moveLeft() {
    positionX -= 1;
}

// move right
void Player::moveRight() {
    positionX += 1;
}