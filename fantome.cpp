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
    this->vitesse = vitesse; //eviter conflit avec parametre de fonction
    aSorti= false;
    direction = sf::Vector2f(0.f, -1.f);
    this->delaiSortie = delaiSortie; // idem que pour vitesse
}
//fonction permettant de gérer totalement le mouvement des fantomes
void Fantome::update(float dt, sf::Vector2f posJoueur, int tileSize, const Grille& grille, sf::Sprite& pacman)
{
    // si aSorti == false → appeler quitterZone
    if (aSorti == false)
        quitterZone(dt, tileSize);
    
    else
        suivreJoueur(dt, posJoueur, tileSize, grille, pacman);

    // si aSorti == true → appeler suivreJoueur
}

// fonction qui fait quitter le fantome de sa zone de départ
void Fantome::quitterZone(float dt, int tileSize)
{
    timerSortie += dt; // permet de compter le temps
    if (timerSortie < delaiSortie) return; // attend avant de bouger

    forme.move(sf::Vector2f(0.f, -1.f) * vitesse * dt); // permet de faire bouger vers le haut les fantomes pour ne pas qu'il reste bloquer au depart

    float sortieY = 9 * tileSize + tileSize / 2.f; // endroit de la sortie en y 
    if (forme.getPosition().y <= sortieY) // si la position en y du fantome est <= endroit de sortie : 
    {
        forme.setPosition({forme.getPosition().x, sortieY}); // on le repositionne pour éviter un décalage dans la grille
        aSorti = true; // on met le boolen a tru epour la fonction generale
        direction = sf::Vector2f(1.f, 0.f); // on le fait bouger vers la droite 
    }
}


// fonction qui suit le joueur 
void Fantome::suivreJoueur(float dt, sf::Vector2f posJoueur, int tileSize, const Grille& grille, sf::Sprite& pacman)
{
    // reccup position pacman 
    sf::Vector2f positionPac = pacman.getPosition();
    //idem pour le fantome
    sf::Vector2f positionFan = forme.getPosition();
    // leur numéro de cellule (+simple que x et y)
    int cellX = (int)(positionFan.x / tileSize);
    int cellY = (int)(positionFan.y / tileSize);
    //le centre de la case
    float centreX = cellX * tileSize + tileSize / 2.f;
    float centreY = cellY * tileSize + tileSize / 2.f;

    float seuil = std::max(vitesse * dt + 1.f, 3.f); // tolérance si la position est pas exact
    bool aligneX = std::abs(positionFan.x - centreX) <= seuil; //on recentre le fantome en x
    bool aligneY = std::abs(positionFan.y - centreY) <= seuil; //et en y 

    // On ne recalcule la direction que si on est dans une NOUVELLE cellule
    bool nouvelleCellule = (cellX != cellulePrecedente.x || cellY != cellulePrecedente.y);

    if (aligneX && aligneY && nouvelleCellule) // s'il est aligné etn x et y et qu'il est dans une nouvelle cellule alors : 
    {
        cellulePrecedente = {cellX, cellY}; // marquer cette cellule comme traitée

        std::vector<sf::Vector2f> directions = { // marque les differentes direction g,d,h,b
            { 1.f,  0.f},
            {-1.f,  0.f},
            { 0.f,  1.f},
            { 0.f, -1.f}
        };

        sf::Vector2f oppose = -direction; //défini l'opposé 
        sf::Vector2f MeillDir = direction; // on intialise la meilleur reiction possible 
        float minDist = std::numeric_limits<float>::max(); // et on definit la plus basse distance ( au départ au max possible pour la faire baisser ensuite)

        for (auto& d : directions) // pour toutes les dirrection slistés dans "directions"
        {
            if (d == oppose ) continue; // si la direction parmi la liste est le demi tour on l'evite 

            int voisinX = cellX + (int)d.x; // la case vosine x et y 
            int voisinY = cellY + (int)d.y;

            if (grille.isWall(voisinX, voisinY, true)) continue; // si la case du voisin est un mur on continue dans la meme direction

            float futurX = voisinX * tileSize + tileSize / 2.f; // on calule la future position
            float futurY = voisinY * tileSize + tileSize / 2.f;
            float distMana = std::abs(futurX - positionPac.x) + std::abs(futurY - positionPac.y); // permet de calculer grace a la distance de manatthan 

            if (distMana < minDist) // si la distance lde manatthan est < a la pluis petite distance trouvé 
            {
                minDist = distMana; // la plus petite distance devient celle calculé
                MeillDir = d; // et la meilleure direction deivent celle qui a ete calculé
            }
        }

        direction = MeillDir; // on lui met la meilleure direction
        forme.setPosition({centreX, centreY}); // snap une seule fois // on le recnetre
    }

    forme.move(direction *vitesse* dt); // on le fait bouger dans la meilleure direction prévue
}

void Fantome::draw(sf::RenderWindow& window) // on dessine le fantome
{
    window.draw(forme);
}