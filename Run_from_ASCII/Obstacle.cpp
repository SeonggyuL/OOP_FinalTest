#include "Obstacle.h"

Obstacle::Obstacle(int x, int y, const std::vector<std::string>& shape)
    : x(x), y(y), shape(shape) {
}

void Obstacle::Update() {
    ++y;
}

void Obstacle::DrawToBuffer(std::vector<std::string>& buffer) const {
    for (int i = 0; i < shape.size(); ++i) {
        int row = y + i;
        if (row < 0 || row >= buffer.size()) continue;
        const std::string& line = shape[i];
        for (int j = 0; j < line.size(); ++j) {
            int col = x + j;
            if (col < 0 || col >= buffer[0].size()) continue;
            if (line[j] != ' ') buffer[row][col] = line[j];
        }
    }
}

bool Obstacle::CheckCollision(int playerX, int playerY) const {
    for (int i = 0; i < shape.size(); ++i) {
        int row = y + i;
        if (row != playerY) continue;
        const std::string& line = shape[i];
        for (int j = 0; j < line.size(); ++j) {
            int col = x + j;
            if (col == playerX && line[j] != ' ') return true;
        }
    }
    return false;
}

bool Obstacle::IsOutOfBounds(int mapHeight) const {
    return y + shape.size() >= mapHeight;
}

bool Obstacle::Intersects(const Obstacle& other) const {
    for (int i = 0; i < shape.size(); ++i) {
        int thisY = y + i;
        if (thisY < other.GetTopY() || thisY > other.GetBottomY()) continue;

        const std::string& thisLine = shape[i];
        for (int j = 0; j < thisLine.size(); ++j) {
            int thisX = x + j;
            if (thisX < other.GetLeftX() || thisX > other.GetRightX()) continue;

            int otherY = thisY - other.y;
            int otherX = thisX - other.x;

            if (otherY >= 0 && otherY < other.shape.size()
                && otherX >= 0 && otherX < other.shape[otherY].size()
                && thisLine[j] != ' ' && other.shape[otherY][otherX] != ' ')
                return true;
        }
    }
    return false;
}

int Obstacle::GetTopY() const { return y; }
int Obstacle::GetBottomY() const { return y + static_cast<int>(shape.size()) - 1; }
int Obstacle::GetLeftX() const { return x; }
int Obstacle::GetRightX() const {
    int maxWidth = 0;
    for (const auto& line : shape)
        if (line.length() > maxWidth)
            maxWidth = static_cast<int>(line.length());
    return x + maxWidth - 1;
}