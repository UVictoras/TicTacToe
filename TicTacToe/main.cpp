#include "GameManager.h"
#include <iostream>

int main()
{
    EventManager::Initialize();
    GameManager::Initialize(); //Initializing GameManager's singleton instance

    GameManager::Get()->GameLoop();

    return 0;
}