#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace sf
{
	class Shape;
	class Color;
	class RenderWindow;
}

class GameObject
{
public:
	bool m_bType;
	float m_fX, m_fY;
	float m_fSizeL, m_fSizeH;
	int m_iIndex;

	char m_sSignFill;


	sf::Vector2f m_fDirection;
	sf::Shape* m_sGraphism;

	GameObject();

	GameObject(bool bType, float fX, float fY, int iIndex, float fSizeL, float fSizeH, sf::Color cColor, sf::Texture* tTexture);

	GameObject(bool bType, float fX, float fY, float fSizeL, float fSizeH, sf::Color cColor);

	void Draw(sf::RenderWindow* oWindow);
};