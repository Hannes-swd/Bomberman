#pragma once
#include "bomb.h"
#include "wall.h"
#include <raylib.h>

enum PlayerType {
    PLAYER_ONE,
    PLAYER_TWO
};

class Player {
    private:
        int speed;
        double positionX;
        double positionY;
        int playerid;
        double bombSetter;
        int bombRange;
        int bombcount;
        int wallCount;
        double lastDamageTime;
        int facingX; 
        int facingY; 

    public:
        int HP;
        Player(int x, int y);

        void setBomb();
        void setWall();
        void drawPlayer(PlayerType type); 
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void takeDamage(int amount);
        bool checkGround(double x, double y);
        void setplayer(int x, int y);
        int getPlayerLive() const;
        int getBombRange() const { return bombRange; }
        int getBombCount() const { return bombcount; }
        double getBombSetter() const { return bombSetter; }
        void addBombRange();
        void addBombCounte();

        double getPositionX() const { return positionX; }
        double getPositionY() const { return positionY; }
};
void playermoovment(Player& player1, Player& player2);