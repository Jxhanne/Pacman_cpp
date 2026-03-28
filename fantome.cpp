// include pour l'affichage
#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include <string>
#include "grille.hpp"
#include <cmath>
// autre
#include <iostream>
#include "fantome.hpp"


Fantome::Fantome(sf::Color couleur, sf::Vector2f positionDepart, float vitesse,float delaiSortie)
{
    // initialiser la forme, couleur, positionFan, taille
    forme.setRadius(12.f);
    forme.setFillColor(couleur);
    forme.setPosition(positionDepart);
    forme.setOrigin(sf::Vector2f(12.f,12.f));
    this->positionDepart = positionDepart;
    this->vitesse = vitesse;
    aSorti= false;
    direction = sf::Vector2f(0.f, -1.f);
    // mettre aSorti = false
    // mettre direction à (0, 0)
    this->delaiSortie = delaiSortie;
}

void Fantome::update(float dt, sf::Vector2f posJoueur, int tileSize, const Grille& grille, sf::Sprite& pacman)
{
    // si aSorti == false → appeler quitterZone
    if (aSorti == false)
        quitterZone(dt, tileSize);
    
    else
        suivreJoueur(dt, posJoueur, tileSize, grille, pacman);

    // si aSorti == true → appeler suivreJoueur
}


void Fantome::quitterZone(float dt, int tileSize)
{
    timerSortie += dt;
    if (timerSortie < delaiSortie) return; // ← attend avant de bouger

    forme.move(sf::Vector2f(0.f, -1.f) * vitesse * dt);

    float sortieY = 9 * tileSize + tileSize / 2.f;
    if (forme.getPosition().y <= sortieY)
    {
        forme.setPosition({forme.getPosition().x, sortieY});
        aSorti = true;
        direction = sf::Vector2f(1.f, 0.f);
    }
}

void Fantome::suivreJoueur(float dt, sf::Vector2f posJoueur, int tileSize, const Grille& grille, sf::Sprite& pacman)
{
    sf::Vector2f positionPac = pacman.getPosition();
    sf::Vector2f positionFan = forme.getPosition();
    int cellX = (int)(positionFan.x / tileSize);
    int cellY = (int)(positionFan.y / tileSize);

    float centreX = cellX * tileSize + tileSize / 2.f;
    float centreY = cellY * tileSize + tileSize / 2.f;

    float seuil = std::max(vitesse * dt + 1.f, 3.f);
    bool aligneX = std::abs(positionFan.x - centreX) <= seuil;
    bool aligneY = std::abs(positionFan.y - centreY) <= seuil;

    // On ne recalcule la direction que si on est dans une NOUVELLE cellule
    bool nouvelleCellule = (cellX != cellulePrecedente.x || cellY != cellulePrecedente.y);

    if (aligneX && aligneY && nouvelleCellule)
    {
        cellulePrecedente = {cellX, cellY}; // ← marquer cette cellule comme traitée

        std::vector<sf::Vector2f> directions = {
            { 1.f,  0.f},
            {-1.f,  0.f},
            { 0.f,  1.f},
            { 0.f, -1.f}
        };

        sf::Vector2f oppose = -direction;
        sf::Vector2f MeillDir = direction;
        float minDist = std::numeric_limits<float>::max();

        for (auto& d : directions)
        {
            if (d == oppose ) continue;

            int voisinX = cellX + (int)d.x;
            int voisinY = cellY + (int)d.y;

            if (grille.isWall(voisinX, voisinY, true)) continue;

            float futurX = voisinX * tileSize + tileSize / 2.f;
            float futurY = voisinY * tileSize + tileSize / 2.f;
            float distMana = std::abs(futurX - positionPac.x) + std::abs(futurY - positionPac.y);

            if (distMana < minDist)
            {
                minDist = distMana;
                MeillDir = d;
            }
        }

        direction = MeillDir;
        forme.setPosition({centreX, centreY}); // snap une seule fois
    }

    forme.move(direction *vitesse* dt);
}

void Fantome::draw(sf::RenderWindow& window)
{
    window.draw(forme);
}

void Fantome::resetPosition()
{
    forme.setPosition(positionDepart);
    aSorti = false;
    timerSortie = 0.f;
    direction = sf::Vector2f(0.f, -1.f);
    cellulePrecedente = {-1, -1};
}