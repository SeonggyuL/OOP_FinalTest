#pragma once

class Player {
public:
    Player(int startX, int mapWidth);
    void MoveLeft();
    void MoveRight();
    int GetX() const;
    int GetY() const;

    void DecreaseHP(int amount);
    int GetHP() const;
private:
    int x;
    const int y;
    int mapWidth;
    int hp = 5;
};
