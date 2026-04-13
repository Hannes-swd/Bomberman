#pragma once
#include "bomb.h"
#include <raylib.h>

enum PlayerType {
    PLAYER_ONE,
    PLAYER_TWO
};

class Player {
    private:
        int HP;
        int speed;
        int positionX;
        int positionY;
        int playerid;
        double bombSetter;

    public:
        Player(int x, int y);

        void setBomb();
        void drawPlayer(PlayerType type); 
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        bool checkGround(double x, double y);
        void setplayer(int x, int y);
        int getPlayerLive() const;
};
void playermoovment(Player& player1, Player& player2);