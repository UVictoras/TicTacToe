#include "GameManager.h"
#include "Math.h"
#include <iostream>
#include <vector>

using namespace std;
sf::Event pressed;

GameManager* GameManager::pInstance = nullptr;

/*
-----------------------------------------------------------------------
|      Following are the functions used in the EventManager maps      |
-----------------------------------------------------------------------
*/

void EventCloseWindow()
{
    GameManager::Get()->CloseWindow();
}

void EventPlaceSign()
{
    GameManager::Get()->PlaceSign();
}

/*
-----------------------------------------------------------------------
|   Following are the methods corresponding to the GameManager Class  |
-----------------------------------------------------------------------
*/

void GameManager::CloseWindow()
{
    oWindow.close();
}

void GameManager::PlaceSign()
{
    std::cout << "init" << endl;
    for (Case* cCase : m_cCasesList)
    {
        if (Math::IsInsideInterval(vLocalPosition.x, cCase->m_fX, cCase->m_fX + cCase->m_fSizeL) == true)
        {
            if (Math::IsInsideInterval(vLocalPosition.y, cCase->m_fY, cCase->m_fY + cCase->m_fSizeH) == true)
            {
                if (m_iTurn % 2 == 0)
                {
                    m_pPlayers[1]->MakePlay(cCase, &m_iTurn, m_tTextureX, m_tTextureCircle);
                }
                else
                {
                    m_pPlayers[0]->MakePlay(cCase, &m_iTurn, m_tTextureX, m_tTextureCircle);
                    sf::RectangleShape oRectangle(sf::Vector2f(50.f, 50.f));
                    oRectangle.setFillColor(sf::Color::Red); 

                }
            }
        }
    }
}

GameManager::GameManager() : oWindow(sf::VideoMode(920, 920), "Casse-Brique") // Calling RenderWindow constructor for our game window
{
    m_bWon1 = false;
    m_bWon2 = false;
    m_bTie = false;

    m_rBackground = new GameObject(true, 0, 0, 920, 920, sf::Color::White);

    CreateGrid();

    m_pPlayers[0] = new Player('x');
    m_pPlayers[1] = new Player('o');

    /*TextureManager::Get()->CreateTexture("img/blank.png", m_tTextureBlank);
    TextureManager::Get()->CreateTexture("img/x.png", m_tTextureX);
    TextureManager::Get()->CreateTexture("img/circle.png", m_tTextureCircle);*/
}

void GameManager::CreateGrid()
{
    //150, 150, (640 + (i * 170)) - ((i / 4) * 170) * 4, 185 + ((i / 4) * 170)

    for (int i = 0; i < 9; i++)
    {
        m_cCasesList[i] = new Case(true, i % 3 * (290 + 25), i / 3 * (290 + 25), i, 290, 290, sf::Color::Black, m_tTextureBlank);
    }
}

void GameManager::CreateSign()
{
    for (int i = 0; i < 9; i++) 
    {
        m_gCasesBack[i] = new GameObject(true, i % 3 * (290 + 25), i / 3 * (290 + 25), i, 290, 290, sf::Color::Red, m_tTextureBlank);
    }
}


void GameManager::CheckWin()
{
    m_bWon1 = false;
}

void GameManager::CheckDraw()
{
    m_bWon2 = false;
}


bool GameManager::IsFullGrid()
{
    for (Case* cCase : m_cCasesList)
    {
        if (cCase->m_bIsFull == false)
        {
            return false;
        }
    }
    return true;
}

void GameManager::CheckTie()
{
    if (IsFullGrid() == false)
    {
        m_bTie = false;
        return;
    }
    m_bTie = true;
}

void GameManager::GameLoop()
{

    sf::Clock oClock;
    float fDeltaTime = oClock.restart().asSeconds();
    sf::Clock clock;
    float fpsLimit = 1 / 120;
    float fps = 0;

    EventManager::Get()->AddComponent(sf::Event::EventType::KeyPressed, sf::Keyboard::Key::Escape, &EventCloseWindow);
    EventManager::Get()->AddComponent(sf::Event::EventType::MouseButtonPressed, sf::Mouse::Left, &EventPlaceSign);

    //GameLoop
    while (oWindow.isOpen() && m_bWon1 == false && m_bWon2 == false && m_bTie == false)
    {

        //EVENT
        EventManager::Get()->Update(&oWindow);

        vLocalPosition = sf::Mouse::getPosition(oWindow);

        //DRAW
        oWindow.clear();

        m_rBackground->Draw(&oWindow);
        for (Case* cCase : m_cCasesList)
        {
            cCase->Draw(&oWindow);
        }


        for (Case* cCase : m_cCasesList)
        {
            cCase->Draw(&oWindow);
        }

        oWindow.display();
        fDeltaTime = oClock.restart().asSeconds();
        if (fDeltaTime < fpsLimit)
        {
            sf::sleep(sf::seconds(fpsLimit - fDeltaTime));
            fDeltaTime += fpsLimit - fDeltaTime;
        }
        fps = 1.f / fDeltaTime;

        CheckWin();
        CheckDraw();
        CheckTie();

    }
}