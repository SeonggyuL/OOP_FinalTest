#include "GameManager.h"
#include "Map.h"
#include "Player.h"
#include "InputHandler.h"
#include "Define.h"
#include "DataManager.h"
#include <windows.h>

GameManager::GameManager() : isRunning(true) {}

void GameManager::Init() {
    DataManager::GetInstance().Load();
    map = std::make_unique<Map>(MAP_WIDTH, MAP_HEIGHT);
    player = std::make_unique<Player>(MAP_WIDTH / 2, MAP_WIDTH);
    inputHandler = std::make_unique<InputHandler>();
}

void GameManager::Run() {
    while (isRunning) {
        map->Clear();
        inputHandler->ProcessInput(*player);
        map->Draw(player->GetX(), MAP_HEIGHT - 1, PLAYER_ICON);
        map->Render();
        Sleep(FRAME_DELAY);
    }
}

void GameManager::Release() {
    DataManager::GetInstance().Save();
}

void GameManager::Stop() { isRunning = false; }
bool GameManager::IsRunning() const { return isRunning; }