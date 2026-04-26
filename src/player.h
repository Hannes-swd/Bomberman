#pragma once
#include "bomb.h"
#include "wall.h"
#include <raylib.h>
#include "player.h"
#include <vector>

enum PlayerType {
    PLAYER_ONE,
    PLAYER_TWO
};
enum items { //inventary
    stone,
    mine,
    remotebomb,
    remotebombdetonator,

    HealingPotion,
};

struct inventar
{
    int count;
    items item;
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
        double lastDamageTime;
        int facingX; 
        int facingY; 
        int selectedItemIndex;
        int activeBombs;

    public:
        int HP;
        Player(int x, int y);

        void setBomb();
        void setWall(Player& p1, Player& p2);
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

        //inventar

        void selectNextItem();
        void selectPreviousItem();
        int getSelectedItemIndex() const { return selectedItemIndex; }
        items getSelectedItem() const;
        bool hasSelectedItem() const { return selectedItemIndex >= 0 && selectedItemIndex < (int)inventarListe.size(); }
        std::vector<inventar> inventarListe;
        void addItem(items item, int amount );
        void removeItem(items item, int amount );
        void useItem(items item);
        bool hasItem(items item) const;
};
void playermoovment(Player& player1, Player& player2);

