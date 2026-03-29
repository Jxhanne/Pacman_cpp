#include "animations_mort.hpp"

void jouerAnimationMort(sf::RenderWindow& window,
                        sf::Sprite& pacman,
                        const std::vector<sf::Texture>& frames)
{
    for (const auto& texture : frames)
    {
        pacman.setTexture(texture, true);

        pacman.setOrigin({
            texture.getSize().x / 2.f,
            texture.getSize().y / 2.f
        });

        window.clear();
        window.draw(pacman);
        window.display();

        sf::Clock clock;
        while (clock.getElapsedTime() < sf::milliseconds(80)) {}
    }
}