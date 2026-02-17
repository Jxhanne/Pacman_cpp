// include pour l'affichage
#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include <string>
#include "grille.hpp"
// autre
#include <iostream>

Grille::Grille(int t)
:   tileSize(t),
    wall(sf::Vector2f((float)t, (float)t)),
    pellet(t * 0.12f)
{
    map = { // plateau de jeu
        "############################",
        "#............##............#",
        "#.####.#####.##.#####.####.#",
        "#.#  #.#   #.##.#   #.#  #.#",
        "#.####.#####.##.#####.####.#",
        "#..........................#",
        "#.####.##.########.##.####.#",
        "#......##....##....##......#",
        "######.#####.##.#####.######",
        "#............##............#",
        "#.####.#####.##.#####.####.#",
        "#...##................##...#",
        "###.##.##.#########.##.##.##",
        "#......##....##....##......#",
        "#.##########.##.##########.#",
        "#..........................#",
        "############################"
    };

    // créartion du mur
    wall.setFillColor(sf::Color::Blue);

    // création point
    pellet.setFillColor(sf::Color::White);
    pellet.setOrigin({pellet.getRadius(), pellet.getRadius()}); // utile pour centrer dans la case les points
}

// fonction qui dessine la grille (PAS de boucle window ici)
void Grille::draw(sf::RenderWindow& window)
{
    // on parcours chaque ligne
    for (int y = 0; y < rows(); ++y)
    {
        // et chaque case dans la ligne
        for (int x = 0; x < cols(); ++x)
        {
            char c = map[y][x]; // c revient à la case précise (coordonnées de rows et de col)
            sf::Vector2f pos{ x * (float)tileSize, y * (float)tileSize }; // calcule la position lié a la tilesize

            // si mur
            if (c == '#')
            {
                wall.setPosition(pos);
                window.draw(wall);
            }
            // si point
            else if (c == '.')
            {
                pellet.setPosition({pos.x + tileSize/2.f, pos.y + tileSize/2.f}); // centrer le point
                window.draw(pellet);
            }
        }
    }
}

// ligne
int Grille::rows() const
{
    return (int)map.size();
}

// colonne
int Grille::cols() const
{
    return (int)map[0].size();
}
