﻿#include "Map.h"
#include <iostream>
#include <windows.h>

Map::Map(int width, int height) : width(width), height(height) {
    buffer.resize(height, std::string(width, ' '));
}

int Map::GetHeight() const {
    return height;
}

int Map::GetWidth() const {
    return width;
}
void Map::Clear() {
    for (auto& row : buffer)
        row = std::string(width, ' ');
}

void Map::Draw(int x, int y, char icon) {
    if (y >= 0 && y < height && x >= 0 && x < width)
        buffer[y][x] = icon;
}

void Map::Render() {
    system("cls");
    for (const auto& row : buffer)
        std::cout << row << '\n';

    // 바닥 출력
    std::cout << std::string(width, '=') << '\n';
}