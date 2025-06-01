#pragma once
#include <vector>
#include <string>

struct ObstacleTemplate {
    std::string name;
    std::vector<std::string> art;
};

class ObstacleLoader {
public:
    static std::vector<ObstacleTemplate> LoadFromFile(const std::string& filepath);
};