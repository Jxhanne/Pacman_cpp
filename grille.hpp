#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Grille {
public: // ce qui va être partagé aux autres codes 
    Grille(int tileSize); // constructeur
    void draw(sf::RenderWindow& window); // afficher le plateau
    int point(int x, int y); // pour manger les points
    int rows() const; // dimensionner la fenêtre
    int cols() const; // egal
    bool isWall(int x, int y,bool estFantome=false) const; // pour les collisions avec les murs
    int bonuspoint = 0; // variable globale pour compter les bonus points
    int vies = 0; // variable globale pour compter les vies
    
    private: // ce qui appartient à la grille en interne 
    std::vector<std::string> map; // la carte
    int tileSize; // taille des tuiles
    sf::RectangleShape wall; // forme du mur
    sf::CircleShape pellet1; // forme du point normal
    sf::CircleShape pellet2; // forme du gros point
    sf::CircleShape pellet3; // forme bonus vie
    sf::CircleShape pellet4; // forme bonus cerise
};
