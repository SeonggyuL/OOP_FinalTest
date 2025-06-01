#pragma once
#include "BaseSingletone.h"
#include "GameData.h"
#include "JsonHelper.h"
#include "Define.h"

class DataManager : public BaseSingleton<DataManager> {
    friend class BaseSingleton<DataManager>;
public:
    GameData& GetData() { return data; }
    void Load() { data = JsonHelper::LoadGameData(SAVE_FILE_PATH); }
    void Save() { JsonHelper::SaveGameData(data, SAVE_FILE_PATH); }

private:
    GameData data;
};