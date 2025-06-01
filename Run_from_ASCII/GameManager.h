#pragma once

#include <memory>
#include "BaseSingletone.h"

class Map;
class Player;
class InputHandler;

class GameManager : public BaseSingleton<GameManager> {
    friend class BaseSingleton<GameManager>;
public:
    void Init();
    void Run();
    void Release();
    void Stop();
    bool IsRunning() const;

private:
    GameManager();
    bool isRunning;
    std::unique_ptr<Map> map;
    std::unique_ptr<Player> player;
    std::unique_ptr<InputHandler> inputHandler;
};