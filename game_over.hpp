#pragma once
#include <SFML/Graphics.hpp>

bool gererMortPacman(
    sf::Sprite& pacman,
    sf::CircleShape& fantome,
    int& vies,
    int tileSize,
    int startX, int startY,
    int ghostStartX, int ghostStartY
);