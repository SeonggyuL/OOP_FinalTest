#pragma once
#include <vector>
#include <string>

class Map {
public:
    Map(int width, int height);
    void Clear();
    void Draw(int x, int y, char icon);
    void Render();
    int GetWidth() const;
    int GetHeight() const;

private:
    int width, height;
    std::vector<std::string> buffer;
};