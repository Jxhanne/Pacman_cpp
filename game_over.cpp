#include <SFML/Graphics.hpp>
#include <cmath>
#include "game_over.hpp"
#include <iostream>

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

bool gererMortPacman(
    sf::Sprite& pacman,
    sf::CircleShape& fantome,
    int& vies,
    int tileSize,
    int startX, int startY,
    int ghostStartX, int ghostStartY
) {
    float rayonFantome = fantome.getRadius();

    if (!collide(pacman, fantome))
        return true; // pas de collision → Pac-Man continue

    // Collision détectée
    vies--;

    if (vies > 0)
    {
        std::cout << "Pac-Man a perdu une vie ! Il en reste : " << vies << "\n";

        // Respawn Pac-Man
        pacman.setPosition({
            startX * tileSize + tileSize / 2.f,
            startY * tileSize + tileSize / 2.f
        });

        // Respawn fantôme
        float rayonFantome = fantome.getRadius();
        fantome.setOrigin({ rayonFantome, rayonFantome });

        fantome.setPosition({
        ghostStartX * tileSize + tileSize / 2.f,
        ghostStartY * tileSize + tileSize / 2.f
    });


        sf::sleep(sf::seconds(1));
        return true; // Pac-Man continue
    }

    // Plus de vies → GAME OVER
    std::cout << "GAME OVER\n";
    return false;
}