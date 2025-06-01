#pragma region Header
#include <iostream>
#include <windows.h>
#include <conio.h>
#pragma endregion

#pragma region MyHeader
#include "GameManager.h"
#include "Map.h"
#include "Player.h"
#include "InputHandler.h"
#include "Define.h"
#include "DataManager.h"
#include "ConsoleUtil.h"
#include "ObstacleLoader.h"
#include "Obstacle.h"
#pragma endregion

GameManager::GameManager() : isRunning(true) {}

void GameManager::Init() {
    int width, height;
    GetConsoleSize(width, height);
    DataManager::GetInstance().Load();
    map = std::make_unique<Map>(width, height);
    player = std::make_unique<Player>(width / 2, width);
    inputHandler = std::make_unique<InputHandler>();
    obstacleTemplates = ObstacleLoader::LoadFromFile("Assets/obstacles.json");

    score = 0;
    currentFrameDelay = FRAME_DELAY;
}

void GameManager::ShowStartScreen() {
    system("cls");
    std::cout << "=========================\n";
    std::cout << "   ASCII DODGE GAME\n";
    std::cout << "=========================\n\n";
    std::cout << "   Press any key to start...\n";
    while (!_kbhit()) Sleep(10);
    _getch(); // 아무 키 입력 대기
}

bool GameManager::ShowGameOverScreen() {
    system("cls");
    std::cout << "=========================\n";
    std::cout << "        GAME OVER\n";
    std::cout << "=========================\n\n";
    std::cout << "Your HP reached 0.\n";
    std::cout << "Try again? (Y/N): ";

    char input;
    std::cin >> input;
    return input == 'y' || input == 'Y';
}

void GameManager::Run() {
    while (isRunning && player->GetHP() > 0) {
        map->Clear();
        inputHandler->ProcessInput(*player);

        // 장애물 생성 주기 (예: 20프레임마다)
        if (++frameCounter % 20 == 0 && !obstacleTemplates.empty()) {
            const auto& tmpl = obstacleTemplates[rand() % obstacleTemplates.size()];
            int maxX = map->GetWidth() - tmpl.art[0].length();
            int spawnX = rand() % (maxX > 0 ? maxX : 1);

            // 기존과 겹치지 않게 확인
            Obstacle newObstacle(spawnX, 0, tmpl.art);
            bool canSpawn = true;
            for (auto& o : obstacles) {
                if (newObstacle.Intersects(*o)) {
                    canSpawn = false;
                    break;
                }
            }

            if (canSpawn)
                obstacles.push_back(std::make_unique<Obstacle>(newObstacle));
        }

        // 장애물 이동 및 충돌 처리
        for (auto it = obstacles.begin(); it != obstacles.end();) {
            (*it)->Update();

            if ((*it)->CheckCollision(player->GetX(), map->GetHeight() - 1)) {
                player->DecreaseHP(1);
                it = obstacles.erase(it);
                continue;
            }

            if ((*it)->IsOutOfBounds(map->GetHeight())) {
                score++;

                // 난이도 증가 조건: 5점마다 속도 증가
                if (score % 5 == 0 && currentFrameDelay > 20)
                    currentFrameDelay -= 5;

                it = obstacles.erase(it);
                continue;
            }
            ++it;
        }

        // 장애물 그리기
        for (const auto& o : obstacles) {
            o->DrawToBuffer(map->buffer); 
        }

        // 플레이어 그리기
        map->Draw(player->GetX(), map->GetHeight() - 1, PLAYER_ICON);

        // 렌더링
        map->Render();
        std::cout << "HP: " << player->GetHP() << "   Score: " << score << "   High Score: " << highScore << '\n';
        // HP 표시
        std::cout << "HP: " << player->GetHP() << '\n';

        Sleep(currentFrameDelay);
    }
    if (score > highScore)
        highScore = score;

    std::cout << "Game Over!\n";
    Sleep(1500);
    Stop();
}

void GameManager::Release() {
    DataManager::GetInstance().Save();
}

void GameManager::Stop() { isRunning = false; }
bool GameManager::IsRunning() const { return isRunning; }