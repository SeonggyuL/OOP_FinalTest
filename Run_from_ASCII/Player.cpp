#include "Player.h"
#include "Define.h"

Player::Player(int startX, int mapWidth)
    : x(startX), y(MAP_HEIGHT - 1), mapWidth(mapWidth) {
}

void Player::MoveLeft() {
    if (x > 0) x--;
}

void Player::MoveRight() {
    if (x < mapWidth - 1) x++;
}

int Player::GetX() const { return x; }
int Player::GetY() const { return y; }