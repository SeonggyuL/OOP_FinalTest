#pragma once

class Player {
public:
    Player(int startX, int mapWidth);
    void MoveLeft();
    void MoveRight();
    int GetX() const;
    int GetY() const;

private:
    int x;
    const int y;
    int mapWidth;
};
