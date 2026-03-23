#include "menu_fin.hpp"
#include <iostream>

ChoixFin afficherMenuFin(sf::RenderWindow& window, int score)
{
    sf::Font font;
    font.openFromFile("assets/PressStart2P-Regular.ttf");

    // Titre du menu de fin 
    sf::Text titre(font, "GAME OVER", 40);
    titre.setFillColor(sf::Color::Red);

    auto tb = titre.getLocalBounds();
    titre.setOrigin({tb.size.x / 2.f, tb.size.y / 2.f});
    titre.setPosition({
        window.getSize().x / 2.f,
        window.getSize().y / 2.f - 120.f
    });

    // Affichage du score
    sf::Text scoreText(font, "Score : " + std::to_string(score), 25);
    scoreText.setFillColor(sf::Color::Yellow);

    auto sb = scoreText.getLocalBounds();
    scoreText.setOrigin({sb.size.x / 2.f, sb.size.y / 2.f});
    scoreText.setPosition({
        window.getSize().x / 2.f,
        window.getSize().y / 2.f - 40.f
    });

    // Bouton pour rejouer 
    sf::Text rejouer(font, "Rejouer", 25);
    rejouer.setFillColor(sf::Color::White);

    auto rb = rejouer.getLocalBounds();
    rejouer.setOrigin({rb.size.x / 2.f, rb.size.y / 2.f});
    rejouer.setPosition({
        window.getSize().x / 2.f,
        window.getSize().y / 2.f + 40.f
    });

    // Bouton pour quitter
    sf::Text quitter(font, "Quitter", 25);
    quitter.setFillColor(sf::Color::White);

    auto qb = quitter.getLocalBounds();
    quitter.setOrigin({qb.size.x / 2.f, qb.size.y / 2.f});
    quitter.setPosition({
        window.getSize().x / 2.f,
        window.getSize().y / 2.f + 100.f
    });

    // Boucle du menu de fin
    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                return ChoixFin::Quitter;

            if (event->is<sf::Event::MouseButtonPressed>())
            {
                auto* mouse = event->getIf<sf::Event::MouseButtonPressed>();
                if (!mouse) continue;

                sf::Vector2f pos(mouse->position.x, mouse->position.y);

                if (rejouer.getGlobalBounds().contains(pos))
                    return ChoixFin::Rejouer;

                if (quitter.getGlobalBounds().contains(pos))
                    return ChoixFin::Quitter;
            }
        }

        window.clear(sf::Color::Black);
        window.draw(titre);
        window.draw(scoreText);
        window.draw(rejouer);
        window.draw(quitter);
        window.display();
    }

    return ChoixFin::Quitter;
}