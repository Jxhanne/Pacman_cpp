#include "animations_mort.hpp"

void jouerAnimationMort(sf::RenderWindow& window,
                        sf::Sprite& pacman,
                        const std::vector<sf::Texture>& mortTextures,
                        float frameTime)
{
    sf::Clock animClock;

    for (int i = 0; i < mortTextures.size(); i++) {

        pacman.setTexture(mortTextures[i]);

        // petite pause entre les frames
        while (animClock.getElapsedTime().asSeconds() < frameTime) {
            // on laisse SFML respirer
        }
        animClock.restart();

        window.clear();
        window.draw(pacman);
        window.display();
    }
}