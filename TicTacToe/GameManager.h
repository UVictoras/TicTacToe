#pragma once
#include "EventManager.h"
#include "Case.h"

typedef void(*func)();
using namespace std;

class GameManager
{
private:
	static GameManager* pInstance;

	sf::Vector2i vLocalPosition;

	sf::RenderWindow oWindow;

	bool bWon, bLost;

public:

	static void Initialize()
	{
		GameManager::pInstance = new GameManager();
	}

	static GameManager* Get()
	{
		return pInstance;
	}

public:

	Case* cCasesList[9];

	int iTurn;

	GameManager();

	void CheckWin();

	void CheckLose();

	void GameLoop();

	//Events

	void CloseWindow();
};