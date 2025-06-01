#include "InputHandler.h"
#include "Define.h"
#include <conio.h>

void InputHandler::ProcessInput(Player& player) {
    if (_kbhit()) {
        char input = _getch();
        switch (input) {
        case KEY_LEFT:
        case 'A': case 'A' - 32:
            player.MoveLeft();
            break;
        case KEY_RIGHT:
        case 'D': case 'D' - 32:
            player.MoveRight();
            break;
        }
    }
}