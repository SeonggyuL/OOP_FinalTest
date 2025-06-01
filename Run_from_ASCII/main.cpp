#include <conio.h>
#include "GameManager.h"
#include "InputHandler.h"
#include "Map.h"
int main() {
    GameManager& game = GameManager::GetInstance();

    do {
        game.ShowStartScreen();
        game.Init();
        game.Run();
        game.Release();
    } while (game.ShowGameOverScreen());

    return 0;
}