#pragma once
#include "bomb.h"
#include <raylib.h>

class Player {
    private:
        int HP;
        int speed;
        int positionX;
        int positionY;

    public:
        Player(int x, int y);

        void setBomb();
        void drawPlayer(Color color);
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
};