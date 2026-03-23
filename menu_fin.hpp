#pragma once
#include <SFML/Graphics.hpp>

enum class ChoixFin {
    Rejouer,
    Quitter
};

ChoixFin afficherMenuFin(sf::RenderWindow& window, int score);