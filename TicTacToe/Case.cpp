#include "Case.h"

Case::Case(bool bType, float fX, float fY, int iIndex, float fSizeL, float fSizeH, sf::Color cColor) : GameObject(bType, fX, fY, fSizeL, fSizeH, cColor)
{
	m_bIsFull = false;
	m_iIndex = iIndex;
}