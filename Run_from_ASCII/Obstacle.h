#pragma once
#include <vector>
#include <string>
class Obstacle
{
public:
    Obstacle(int x, int y, const std::vector<std::string>& shape);
    void Update();
    void DrawToBuffer(std::vector<std::string>& buffer) const;
    bool CheckCollision(int playerX, int playerY) const;
    bool Intersects(const Obstacle& other) const;
    bool IsOutOfBounds(int mapHeight) const;
    int GetTopY() const;
    int GetBottomY() const;
    int GetLeftX() const;
    int GetRightX() const;
private:
    int x, y;
    std::vector<std::string> shape;

};

