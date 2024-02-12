#include "GameManager.h"
#include <iostream>


int main()
{
   
   // EventManager::Get()->AddComponent(sf::Event::EventType::KeyPressed, sf::Keyboard::Key::Enter, &EventCloseWindow);
    sf::RenderWindow window(sf::VideoMode(400, 200), "Entrer le nom d'utilisateur");

    sf::Font font;
    if (!font.loadFromFile("srcs/font/Roboto-Black.ttf")) {
        std::cerr << "Erreur lors du chargement de la police" << std::endl;
        return 1;
    }

    sf::Text instruction("Entrez votre nom d'utilisateur :", font, 20);
    instruction.setPosition(10, 10);

    sf::Text inputText("", font, 20);
    inputText.setPosition(10, 50);

    std::string username;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    char enteredChar = static_cast<char>(event.text.unicode);
                    if (enteredChar == '\b' && !username.empty()) {
                        // Backspace : supprimer le dernier caractère
                        username.pop_back();
                    }
                    else if (enteredChar != '\b') {
                        // Ajouter le caractère à la chaîne du nom d'utilisateur
                        username += enteredChar;
                    }

                    // Vérifier si la touche Entrée est pressée
                    
                }
                    // Mettre à jour le texte affiché
                    inputText.setString(username);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
                window.close();
        }

        window.clear();
        window.draw(instruction);
        window.draw(inputText);
        window.display();
    }

    std::cout << "Nom d'utilisateur saisi : " << username << std::endl;

    EventManager::Initialize();
    GameManager::Initialize(); //Initializing GameManager's singleton instance
    TextureManager::Initialize();

    GameManager::Get()->GameLoop();

    return 0;
}