#include "GameManager.h"
#include <iostream>

int main()
{
    EventManager::Initialize();
    GameManager::Initialize(); //Initializing GameManager's singleton instance
    TextureManager::Initialize();

    GameManager::Get()->GameLoop();

    return 0;
}