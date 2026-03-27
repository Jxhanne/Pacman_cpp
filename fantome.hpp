#pragma once
#include <SFML/Graphics.hpp>
#include "grille.hpp"

class Fantome
{
public:
    Fantome(sf::Color couleur, sf::Vector2f positionDepart, float vitesse,float delaiSortie);

    void update(float dt, sf::Vector2f posJoueur, int tileSize, const Grille& grille, sf::Sprite& pacman);
    void draw(sf::RenderWindow& window);

private:
    void quitterZone(float dt, int tileSize);
    void suivreJoueur(float dt, sf::Vector2f posJoueur, int tileSize, const Grille& grille, sf::Sprite& pacman);

    sf::CircleShape forme;
    sf::Vector2f direction;
    float vitesse;
    bool aSorti;
    sf::Vector2i cellulePrecedente = {-1, -1};
    float delaiSortie;
    float timerSortie = 0.f;
};