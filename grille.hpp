#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Grille {
public: // ce qui va être partagé aux autres codes 
    Grille(int tileSize); // constructeur
    void draw(sf::RenderWindow& window); // afficher le plateau 
    void point(int x, int y); // pour manger les points
    int rows() const; // dimensionner la fenêtre
    int cols() const; // egal
    bool isWall(int x, int y) const; // ne pas traverser les murs 

private: // ce qui appartient à la grille en interne 
    std::vector<std::string> map; // la carte
    int tileSize; // taille des tuiles 

    sf::RectangleShape wall; // forme du mur 
    sf::CircleShape pellet; // forme de la nourriture
};
