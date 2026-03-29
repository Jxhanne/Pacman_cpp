#include "animations_mort.hpp"

void jouerAnimationMort(sf::RenderWindow& window, sf::Sprite& pacman, const std::vector<sf::Texture>& frames)
    {
        for (const auto& texture : frames)  // Boucle sur toutes les frames de l'animation
        {
            pacman.setTexture(texture, true);

            pacman.setOrigin({
                texture.getSize().x / 2.f,
                texture.getSize().y / 2.f  // Centre le sprite 
            });

            window.clear();
            window.draw(pacman);
            window.display();    // Dessine la frame actuelle

            sf::Clock clock;
            while (clock.getElapsedTime() < sf::milliseconds(80)) {} // Delais entre chaque frame 
        }
    }