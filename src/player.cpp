#include "player.h"

Player::Player(int x, int y) : HP(10), speed(0), positionX(x), positionY(y) {}

void Player::setBomb() {
    Bomb bomb(positionX, positionY);
}