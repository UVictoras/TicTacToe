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
    for (Case* cCase : m_cCasesList)
    {
        if (Math::IsInsideInterval(vLocalPosition.x, cCase->m_fX, cCase->m_fX + cCase->m_fSizeL) == true)
        {
            if (Math::IsInsideInterval(vLocalPosition.y, cCase->m_fY, cCase->m_fY + cCase->m_fSizeH) == true)
            {
                if (m_iTurn % 2 == 0)
                {
                    if (m_gCasesBack[cCase->m_iIndex] == nullptr) {
                        m_gCasesBack[cCase->m_iIndex] = new GameObject(true, cCase->m_fX + 290 / 2 - 100, cCase->m_fY + 290 / 2 - 100, 200, 200, sf::Color::Red);
                        m_iTurn++;
                    }

                    //m_pPlayers[1]->MakePlay(cCase, &m_iTurn, m_tTextureX, m_tTextureCircle);

                }
                else
                {
                    if (m_gCasesBack[cCase->m_iIndex] == nullptr) {
                        m_gCasesBack[cCase->m_iIndex] = new GameObject(false, cCase->m_fX + 290 / 2 - 100, cCase->m_fY + 290 / 2 - 100, 100, 100, sf::Color::White);
                        m_iTurn++;
                    }
                    //m_pPlayers[0]->MakePlay(cCase, &m_iTurn, m_tTextureX, m_tTextureCircle);
                    //sf::RectangleShape oRectangle(sf::Vector2f(50.f, 50.f));
                    //oRectangle.setFillColor(sf::Color::Red); 

                }
            }
        }
    }
}

GameManager::GameManager() : oWindow(sf::VideoMode(920, 920), "Casse-Brique") // Calling RenderWindow constructor for our game window
{
    m_bWon1 = false;
    m_bWon2 = false;
    m_bDraw = false;

    m_rBackground = new GameObject(true, 0, 0, 920, 920, sf::Color::White);

    CreateGrid();
    CreateSign();

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
        //m_gCasesBack[i] = new GameObject(true, i % 3 * (290 + 25), i / 3 * (290 + 25), 290, 290, sf::Color::White);
        m_gCasesBack[i] = nullptr;
    }
}


void GameManager::CheckWin()
{
    m_bWon1 = false;
    m_bWon2 = false;

    // VERIFICATION COLUMN
    for (int x = 0; x < 3; x++) {
        if (m_gCasesBack[x] != nullptr and m_gCasesBack[x + 3] != nullptr and m_gCasesBack[x + 6] != nullptr) {
            if (m_gCasesBack[x]->m_bType == m_gCasesBack[x + 3]->m_bType and m_gCasesBack[x + 6]->m_bType == m_gCasesBack[x]->m_bType) {
                if (m_gCasesBack[x]->m_bType == true)
                    m_bWon1 = true;
                else
                    m_bWon2 = true;
            }
        }
    }

    // VERIFICATION LINE
    for (int y = 0; y < 3; y++) {
        if (m_gCasesBack[y * 3] != nullptr and m_gCasesBack[y * 3 + 1] != nullptr and m_gCasesBack[y * 3 + 2] != nullptr) {
            if (m_gCasesBack[y * 3]->m_bType == m_gCasesBack[y * 3 + 1]->m_bType and m_gCasesBack[y * 3 + 2]->m_bType == m_gCasesBack[y * 3]->m_bType) {
                if (m_gCasesBack[y * 3]->m_bType == true)
                    m_bWon1 = true;
                else
                    m_bWon2 = true;
            }
        }
    }

    // VERIFICATION DIAGONAL
    if (m_gCasesBack[0] != nullptr and m_gCasesBack[4] != nullptr and m_gCasesBack[8] != nullptr){
        if (m_gCasesBack[0]->m_bType == m_gCasesBack[4]->m_bType and m_gCasesBack[8]->m_bType == m_gCasesBack[0]->m_bType) {
            if (m_gCasesBack[0]->m_bType == true)
                m_bWon1 = true;
            else
                m_bWon2 = true;
        }
    }
    if (m_gCasesBack[2] != nullptr and m_gCasesBack[4] != nullptr and m_gCasesBack[6] != nullptr) {
        if (m_gCasesBack[2]->m_bType == m_gCasesBack[4]->m_bType and m_gCasesBack[6]->m_bType == m_gCasesBack[2]->m_bType) {
            if (m_gCasesBack[2]->m_bType == true)
                m_bWon1 = true;
            else
                m_bWon2 = true;
        }
    }

}

void GameManager::CheckDraw()
{
    for (GameObject* cCase : m_gCasesBack)
    {
        if (cCase == nullptr) {
            m_bDraw = false;
            return;
        }

    }
    m_bDraw = true;
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
    while (oWindow.isOpen() && m_bWon1 == false && m_bWon2 == false && m_bDraw == false)
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

        for (GameObject* cCase : m_gCasesBack)
        {
            if (cCase != nullptr) {
                cCase->Draw(&oWindow);
            }
            
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
        if (m_bWon1)
            cout << "Joueur 1 a gagne" << endl;
        else if (m_bWon2)
            cout << "Joueur 2 a gagne" << endl;
        else if (m_bDraw)
            cout << "Egalite" << endl;
    }
}