#pragma once
#include "GameData.h"
#include "json.hpp"
#include <fstream>

namespace JsonHelper {
    inline void SaveGameData(const GameData& data, const std::string& path) {
        nlohmann::json j;
        j["score"] = data.score;
        j["highScore"] = data.highScore;
        std::ofstream out(path);
        out << j.dump(4);
    }

    inline GameData LoadGameData(const std::string& path) {
        GameData data;
        std::ifstream in(path);
        if (in.is_open()) {
            nlohmann::json j;
            in >> j;
            data.score = j.value("score", 0);
            data.highScore = j.value("highScore", 0);
        }
        return data;
    }
}