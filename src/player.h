#pragma once
#include "bomb.h"
#include <raylib.h>

class Player {
    private:
        int HP;
        int speed;
        int positionX;
        int positionY;
        int playerid;

    public:
        Player(int x, int y);

        void setBomb();
        void drawPlayer(Color color);
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void setplayer(int x, int y);
};