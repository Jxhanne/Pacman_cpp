#include <SFML/Graphics.hpp>
#include <cmath>
#include "game_over.hpp"
#include <iostream>
#include "animations_mort.hpp"

static bool collide(const sf::Sprite& pacman, const sf::CircleShape& fantome)
{
    // centres
    sf::Vector2f p = pacman.getPosition();
    sf::Vector2f f = fantome.getPosition();

    float dx = p.x - f.x;
    float dy = p.y - f.y;

    // distance au carré
    float dist2 = dx*dx + dy*dy;

    // rayons (SFML 3 → size.x)
    float rayonPacman  = pacman.getGlobalBounds().size.x / 2.f;
    float rayonFantome = fantome.getRadius();

    float somme = rayonPacman + rayonFantome;

    return dist2 <= somme * somme;
}

bool gererMortPacman(sf::Sprite& pacman,
                     sf::CircleShape& fantome,
                     int& vies,
                     int tileSize,
                     int startX, int startY,
                     int ghostStartX, int ghostStartY,
                     sf::RenderWindow& window,
                     const std::vector<sf::Texture>& mortTextures)
{
    if (!collide(pacman, fantome))
        return true;

    vies--;

    // --- ANIMATION DE MORT ---
    jouerAnimationMort(window, pacman, mortTextures);

    if (vies <= 0)
        return false;

    // respawn pacman
    pacman.setPosition({
        startX * tileSize + tileSize / 2.f,
        startY * tileSize + tileSize / 2.f
    });

    // respawn fantôme
    fantome.setPosition({
        ghostStartX * tileSize + tileSize / 2.f,
        ghostStartY * tileSize + tileSize / 2.f
    });

    return true;
}