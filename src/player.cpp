#include "player.h" // include playerclass from player.h
#include "raylib.h"
#include "bomb.h"
#include "player.h"
#include "textures.h"
#include "wall.h"
#include "map.h"
#include "mine.h"
#include "item.h"


Player::Player(int x, int y) : HP(10), 
speed(0), 
positionX(x), 
positionY(y), 
bombSetter(0), 
bombRange(1), 
lastDamageTime(0), 
bombcount(1),
facingX(0),
facingY(0),
selectedItemIndex(-1),
activeBombs(0)
{}

void Player::takeDamage(int amount) {
    if (GetTime() - lastDamageTime < 3.0) return; // Cooldown
    HP -= amount;
    lastDamageTime = GetTime();
}

void Player::setBomb() {
    activeBombs = 0;
    double now = GetTime();
    
    for (const auto& bomb : BombList) {
        if (now - bomb.spawnTime < 3.0 && bomb.owner == this) {
            activeBombs++;
        }
    }
    if (activeBombs < bombcount) {
        placeBomb(positionX, positionY, bombRange, this);
    }
}

void Player::setWall(Player& p1, Player& p2) {
    int stoneCount = 0;
    int gridX = (int)((positionX + facingX * 32) / 32);
    int gridY = (int)((positionY + facingY * 32) / 32);

    for (const auto& slot : inventarListe) {
        if (slot.item == stone) {
            stoneCount = slot.count;
            break;
        }
    }

    int p1x = (int)(p1.getPositionX() / 32);
    int p1y = (int)(p1.getPositionY() / 32);
    int p2x = (int)(p2.getPositionX() / 32);
    int p2y = (int)(p2.getPositionY() / 32);

    if (gridX == p1x && gridY == p1y) return;
    if (gridX == p2x && gridY == p2y) return;

    if (0 < stoneCount) {

        if (currentMap.data[gridY][gridX] == TILE_FLOOR) {
            drawWall(positionX + facingX * 32, positionY + facingY * 32, p1, p2);
            removeItem(stone, 1);
        }
    }
}


void Player::selectNextItem() {
    if (inventarListe.empty()) {
        selectedItemIndex = -1;
        return;
    }
    
    if (selectedItemIndex == -1) {
        selectedItemIndex = 0;
    } else {
        selectedItemIndex++;
        if (selectedItemIndex >= (int)inventarListe.size()) {
            selectedItemIndex = 0;
        }
    }
}

void Player::selectPreviousItem() {
    if (inventarListe.empty()) {
        selectedItemIndex = -1;
        return;
    }
    
    if (selectedItemIndex == -1) {
        selectedItemIndex = (int)inventarListe.size() - 1;
    } else {
        selectedItemIndex--;
        if (selectedItemIndex < 0) {
            selectedItemIndex = (int)inventarListe.size() - 1;
        }
    }
}

items Player::getSelectedItem() const {
    if (hasSelectedItem()) {
        return inventarListe[selectedItemIndex].item;
    }
    return stone; 
}



// move up
void Player::moveUp() {
    if(checkGround(positionX, positionY - 1.5)) {
        positionY -= 1.5;
        facingY = -2;
        facingX = 0;
    }
}

// move Down
void Player::moveDown() {
    if(checkGround(positionX, positionY + 1.5)) {
        positionY += 1.5;
        facingY = 2;
        facingX = 0;
    }
}

// move left
void Player::moveLeft() {
    if(checkGround(positionX - 1.5, positionY)) {
        positionX -= 1.5;
        facingY = 0;
        facingX = -2;
    }
}

// move right
void Player::moveRight() {
    if(checkGround(positionX + 1.5, positionY)) {
        positionX += 1.5;
        facingY = 0;
        facingX = 2;
    }
}

void Player::addItem(items item, int amount ) {
    for (auto& slot : inventarListe) {
        if (slot.item == item) {
            slot.count += amount; 
            return;
        }
    }
    
    inventarListe.push_back({amount, item});
}

void Player::removeItem(items item, int amount) {
    for (auto it = inventarListe.begin(); it != inventarListe.end(); ++it) {
        if (it->item == item) {
            it->count -= amount;
            if (it->count <= 0) {
                inventarListe.erase(it);
            }
            return;
        }
    }
}

void Player::drawPlayer(PlayerType type) {
    if (type == PLAYER_ONE) {
        float scale = 16.0f / textures["player1"].width;
        float drawX = (float)positionX - (textures["player1"].width * scale) / 2.0f;
        float drawY = (float)positionY - (textures["player1"].height * scale) / 2.0f;
        DrawTextureEx(textures["player1"], { drawX, drawY }, 0, scale, WHITE);
    }
    if (type == PLAYER_TWO) {
        float scale = 16.0f / textures["player2"].width;
        float drawX = (float)positionX - (textures["player2"].width * scale) / 2.0f;
        float drawY = (float)positionY - (textures["player2"].height * scale) / 2.0f;
        DrawTextureEx(textures["player2"], { drawX, drawY }, 0, scale, WHITE);
    }
}

void Player::setplayer(int x, int y) {
    positionX = x;
    positionY = y;
}
int Player::getPlayerLive() const {
    return HP;
}

// int Player::getBombCount() const {
//    return bombcount;
// }

bool Player::checkGround(double x, double y) {
    int margin = 14; 
    
    // check ALL corner
    int corners[4][2] = {
        { (int)(x - margin) / 32, (int)(y - margin) / 32 }, // left up
        { (int)(x + margin) / 32, (int)(y - margin) / 32 }, // right up
        { (int)(x - margin) / 32, (int)(y + margin) / 32 }, // left down
        { (int)(x + margin) / 32, (int)(y + margin) / 32 }, // right down
    };

    for (auto& c : corners) {
        if (c[1] < 0 || c[0] < 0) return false; // corner check
        if (currentMap.data[c[1]][c[0]] != TILE_FLOOR) return false; // floor check
    }
    return true;
}

void playermoovment(Player& player1, Player& player2) {
    if(IsKeyDown(KEY_W))
        player1.moveUp();

    if (IsKeyDown(KEY_S))
        player1.moveDown();

    if (IsKeyDown(KEY_A))
        player1.moveLeft();

    if (IsKeyDown(KEY_D))
        player1.moveRight();

    if (IsKeyPressed(KEY_TWO)) {
        player1.selectPreviousItem();
    }
    if (IsKeyPressed(KEY_THREE)) {
        player1.selectNextItem();
    }

    if (IsKeyPressed(KEY_EIGHT)) {
        player2.selectPreviousItem();
    }
    if (IsKeyPressed(KEY_NINE)) {
        player2.selectNextItem();
    }
    if (IsKeyDown(KEY_I))
        player2.moveUp();

    if (IsKeyDown(KEY_K))
        player2.moveDown();

    if (IsKeyDown(KEY_J))
        player2.moveLeft();

    if (IsKeyDown(KEY_L))
        player2.moveRight();

    if (IsKeyPressed(KEY_Q))
        player1.setBomb();

    if (IsKeyPressed(KEY_U))
    {
        player2.setBomb();
    }

    if (IsKeyPressed(KEY_E))
    {
        //use item player 1
        items aktuellesitem = player1.getSelectedItem();
        if (aktuellesitem == stone)
            player1.setWall(player1, player2);
        if (aktuellesitem == mine)
            player1.useItem(mine);
    }

    if (IsKeyPressed(KEY_O))
    {
        //use item player 2
        items aktuellesitem = player2.getSelectedItem();
        if (aktuellesitem == stone)
            player2.setWall(player1, player2);
        if (aktuellesitem == mine)
            player2.useItem(mine);
    }

    if (isPlayerInExplosion(player1.getPositionX(), player1.getPositionY()))
        player1.takeDamage(2);

    if (isPlayerInExplosion(player2.getPositionX(), player2.getPositionY()))
        player2.takeDamage(2);
}

void Player::addBombRange() {
    bombRange++;
}

void Player::addBombCounte() {
    bombcount++;
}

void Player::useItem(items item) {
    switch (item) {
        case mine:
            setmine(positionX,positionY);
            break;
        default:
            break;
    }
}