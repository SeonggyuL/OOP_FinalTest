#pragma once


#pragma region Header
#include <memory>
#include <vector>
#pragma endregion
#pragma region MyHeader
#include "Define.h"
#include "BaseSingletone.h"
#include "Obstacle.h"
#include "ObstacleLoader.h"
#pragma endregion


class Map;
class Player;
class InputHandler;
class Obstacle;


class GameManager : public BaseSingleton<GameManager> {
    friend class BaseSingleton<GameManager>;
public:
    int score = 0;
    int highScore = 0;
    int currentFrameDelay = FRAME_DELAY;

public:
    void Init();
    void Run();
    void Release();
    void Stop();
    bool IsRunning() const;

    void ShowStartScreen();
    bool ShowGameOverScreen();

    std::unique_ptr<Map> map;

private:
    GameManager();
    bool isRunning;
   
    std::unique_ptr<Player> player;
    std::unique_ptr<InputHandler> inputHandler;

    std::vector<std::unique_ptr<Obstacle>> obstacles;
    std::vector<ObstacleTemplate> obstacleTemplates;
    int frameCounter = 0;
};