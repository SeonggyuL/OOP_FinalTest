#include "ObstacleLoader.h"
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

std::vector<ObstacleTemplate> ObstacleLoader::LoadFromFile(const std::string& filepath) {
    std::vector<ObstacleTemplate> templates;
    std::ifstream in(filepath);
    if (!in.is_open()) return templates;

    json j;
    in >> j;

    for (const auto& item : j) {
        ObstacleTemplate t;
        t.name = item.value("name", "");
        t.art = item.value("art", std::vector<std::string>{});
        templates.push_back(t);
    }

    return templates;
}
