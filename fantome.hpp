#pragma once
#include <SFML/Graphics.hpp>
#include "grille.hpp"

class Fantome
{
public:
    Fantome(sf::Color couleur, sf::Vector2f positionDepart, float vitesse,float delaiSortie); // def fantome 

    void update(float dt, sf::Vector2f posJoueur, int tileSize, const Grille& grille, sf::Sprite& pacman); // def fonction mouvement general
    void draw(sf::RenderWindow& window); // def fonction draw

private:

    // def fonction qui vont être implémentés dans la focntion update
    void quitterZone(float dt, int tileSize);
    void suivreJoueur(float dt, sf::Vector2f posJoueur, int tileSize, const Grille& grille, sf::Sprite& pacman);
    
    // forme du fantome
    sf::CircleShape forme;
    // direction
    sf::Vector2f direction;
    //vitesse
    float vitesse;
    // booléen pour savoir s'il est sorti de la zone de départ
    bool aSorti;
    // retrouver cellule préc pour ne pas recacluler trop vite les directions
    sf::Vector2i cellulePrecedente = {-1, -1};
    // permet de faire sortir les fantome avec un ecart
    float delaiSortie;
    float timerSortie = 0.f;
};