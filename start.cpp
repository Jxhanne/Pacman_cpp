#include "start.hpp"

bool showStartScreen(sf::RenderWindow& window) {

    sf::Font font;
    if (!font.openFromFile("assets/PressStart2P-Regular.ttf")) {
        return false;
    }

    // Affichage du bouton "START"
    sf::Vector2f buttonSize(250.f, 90.f);
    sf::RectangleShape button(buttonSize);
    button.setFillColor(sf::Color(50, 50, 200));

    // centrer le bouton
    button.setOrigin({buttonSize.x / 2.f, buttonSize.y / 2.f});
    button.setPosition({
        window.getSize().x / 2.f,
        window.getSize().y / 2.f
    });

    // Texte du bouton "START"
    sf::Text startText(font, "START", 35);
    startText.setFillColor(sf::Color::White);

    // centrer le texte dans le bouton
    auto tb = startText.getLocalBounds();
    startText.setOrigin({tb.size.x / 2.f, tb.size.y / 2.f});
    startText.setPosition(button.getPosition());

    // Boucle d'attente sur l'écran de début
    while (window.isOpen()) {

        while (auto event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (event->is<sf::Event::MouseButtonPressed>()) {
                auto* mouse = event->getIf<sf::Event::MouseButtonPressed>();
                if (!mouse) continue;

                sf::Vector2f pos(mouse->position.x, mouse->position.y);

                if (button.getGlobalBounds().contains(pos)) {
                    return true;
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(button);
        window.draw(startText);
        window.display();
    }

    return false;
}