#include "game_over.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <optional>

bool afficherGameOver(sf::RenderWindow& window, int score)
{
    sf::Font font("assets/arial.ttf");

    sf::Text titre(font, "GAME OVER", 60);
    titre.setFillColor(sf::Color::Red);
    titre.setPosition({200.f, 150.f});

    sf::Text scoreText(font, "Score : " + std::to_string(score), 40);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({200.f, 230.f});

    sf::RectangleShape boutonRejouer({250.f, 60.f});
    boutonRejouer.setFillColor(sf::Color(50, 150, 50));
    boutonRejouer.setPosition({200.f, 330.f});

    sf::Text txtRejouer(font, "Rejouer", 35);
    txtRejouer.setFillColor(sf::Color::White);
    txtRejouer.setPosition({240.f, 340.f});

    sf::RectangleShape boutonQuitter({250.f, 60.f});
    boutonQuitter.setFillColor(sf::Color(150, 50, 50));
    boutonQuitter.setPosition({200.f, 420.f});

    sf::Text txtQuitter(font, "Quitter", 35);
    txtQuitter.setFillColor(sf::Color::White);
    txtQuitter.setPosition({250.f, 430.f});

    while (window.isOpen())
    {
        while (auto opt = window.pollEvent())
        {
            sf::Event e = *opt; // extraction de l'événement

            // Fermeture fenêtre
            if (e.type == sf::Event::Closed)
                return false;

            // Clic souris
            if (e.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mouse = sf::Mouse::getPosition(window);
                sf::Vector2f mouseF((float)mouse.x, (float)mouse.y);

                if (boutonRejouer.getGlobalBounds().contains(mouseF))
                    return true;

                if (boutonQuitter.getGlobalBounds().contains(mouseF))
                    return false;
            }
        }

        window.clear(sf::Color::Black);
        window.draw(titre);
        window.draw(scoreText);
        window.draw(boutonRejouer);
        window.draw(txtRejouer);
        window.draw(boutonQuitter);
        window.draw(txtQuitter);
        window.display();
    }

    return false;
}