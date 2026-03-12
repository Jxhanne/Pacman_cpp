#include "start.hpp"

bool showStartScreen(sf::RenderWindow& window) {

    // Charger la police d'écriture
    sf::Font font;

    // Vérifier si la police a été chargée correctement
    if (!font.openFromFile("assets/PressStart2P-Regular.ttf")) {
        return false; // on quitte l'écran de début si la police n'est pas trouvée
    }
    
    font.openFromFile("assets/PressStart2P-Regular.ttf");

    // Affiche le texte
    sf::Text startText(font, "START", 35); 
    startText.setFillColor(sf::Color::White);
    startText.setPosition({330.f, 260.f}); 

    // Le bouton pour lancer le jeu 
    sf::RectangleShape button({200.f, 80.f});
    button.setFillColor(sf::Color(50, 50, 200));
    button.setPosition({315.f, 240.f});

    // Quand on clique sur le bouton, ça lance le jeu 
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (event->is<sf::Event::MouseButtonPressed>()) {
                auto mouse = sf::Mouse::getPosition(window);

                if (button.getGlobalBounds().contains(
                        sf::Vector2f(mouse.x, mouse.y))) {
                    return true;
                }
            }
        }

        window.clear(sf::Color::Black); // fond noir 
        window.draw(button); // dessine le bouton 
        window.draw(startText); // écrit le texte
        window.display();
    }

    return false;
}