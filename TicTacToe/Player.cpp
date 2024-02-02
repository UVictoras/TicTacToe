#include "Player.h"

Player::Player(char sSign, bool bType, float fX, float fY, float fSizeL, float fSizeH, sf::Color cColor) : GameObject(bType, fX, fY, fSizeL, fSizeH, cColor)
{
	m_sSign = sSign;
}

void Player::MakePlay(Case* cCase, int* iTurn)
{
	if (cCase->m_bIsFull == true)
		return;

	cCase->m_sSignFill = m_sSign;
	cCase->m_bIsFull = true;
	iTurn++;
}