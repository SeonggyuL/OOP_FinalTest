#include "GameManager.h"

int main() {
    GameManager& game = GameManager::GetInstance();
    game.Init();
    game.Run();
    game.Release();
    return 0;
}