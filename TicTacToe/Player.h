#pragma once
#include "GameObject.h";
#include "Case.h";

class Player : public GameObject
{
public:
	char m_sSign; 
	
	Player(char sSign, bool bType, float fX, float fY, float fSizeL, float fSizeH, sf::Color cColor);

	void MakePlay(Case* cCase, int* iTurn);
};