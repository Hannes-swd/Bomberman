#pragma once
#include "bomb.h"

class Player {
    private:
        int HP;
        int speed;
        int positionX;
        int positionY;

    public:
        Player(int x, int y);

        void setBomb();
};