// include pour l'affichage
#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include <string>
#include "grille.hpp"
// autre
#include <iostream>

Grille::Grille(int t)
: tileSize(t),
  wall(sf::Vector2f((float)t, (float)t)),
  pellet1(t * 0.12f),
  pellet2(t * 0.24f),
  pellet3(t * 0.24f),
  pellet4(t * 0.24f)
{
    map = { // plateau de jeu
    "############################",
    "#............##............#",
    "#.####.#####.##.#####.####.#",
    "#.####.#####.##.#####.####.#",
    "#..........................#",
    "#.####.##.########.##.####.#",
    "#.####.##.########.##.####.#",
    "#..b...##....##....##...b..#",
    "######.#####.##.#####.######",
    " ............##............ ",
    "#.####.#####....#####.####.#",
    "#.####.##   #--#   ##.####.#",
    "#......##   #  #   ##..b...#",
    "#.######### #  # #########.#",
    "#.######### #### #########.#",
    "#...........    ...........#",
    "#.####.##.########.##.####.#",
    "#.####.##.########.##.####.#",
    "#..v....................b..#",
    "############################",
}
;

    // créartion du mur
    wall.setFillColor(sf::Color::Blue);

<<<<<<< HEAD
    //création point
    pellet1.setFillColor(sf::Color::Yellow); // jaune
    pellet1.setOrigin({pellet1.getRadius(), pellet1.getRadius()}); // centrer le point
    pellet2.setFillColor(sf::Color::Yellow); // jaune
    pellet2.setOrigin({pellet2.getRadius(), pellet2.getRadius()}); // centrer le point
    pellet3.setFillColor(sf::Color(144, 238, 144)); // vert pastelle
    pellet3.setOrigin({pellet3.getRadius(), pellet3.getRadius()}); // centrer le point
    pellet4.setFillColor(sf::Color::Red); // rouge
    pellet4.setOrigin({pellet4.getRadius(), pellet4.getRadius()}); // centrer le point
=======
    // création point
    pellet.setFillColor(sf::Color::White);
    pellet.setOrigin({pellet.getRadius(), pellet.getRadius()}); // utile pour centrer dans la case les points

    // création grps points
    gros_pellet.setFillColor(sf::Color::White);
    gros_pellet.setOrigin({gros_pellet.getRadius(), gros_pellet.getRadius()}); // utile pour centrer dans la case les points
>>>>>>> 9142afbd7ee61ec9861e1b1d8c736fbeb8e201a8
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
                pellet1.setOrigin({pellet1.getRadius(), pellet1.getRadius()}); // centrer le point
                pellet1.setPosition({pos.x + tileSize/2.f, pos.y + tileSize/2.f}); // centrer le point
                window.draw(pellet1);
            }
            // si bonus point
            else if (c == 'b')
            {
                pellet2.setOrigin({pellet2.getRadius(), pellet2.getRadius()}); // centrer le point
                pellet2.setPosition({pos.x + tileSize/2.f, pos.y + tileSize/2.f}); // centrer le point
                window.draw(pellet2);
            }
            // si super bonus vie
            else if (c == 'v')
            {
                pellet3.setOrigin({pellet3.getRadius(), pellet3.getRadius()}); // centrer le point
                pellet3.setPosition({pos.x + tileSize/2.f, pos.y + tileSize/2.f}); // centrer le point
                window.draw(pellet3);
            }
            // si cerise
            else if (c == 'c')
            {
                pellet4.setOrigin({pellet4.getRadius(), pellet4.getRadius()}); // centrer le point
                pellet4.setPosition({pos.x + tileSize/2.f, pos.y + tileSize/2.f}); // centrer le point
                window.draw(pellet4);
            }
            else if (c == '*')
            {
                gros_pellet.setPosition({pos.x + tileSize/2.f, pos.y + tileSize/2.f}); // centrer le point
                window.draw(gros_pellet);
            }
        }
    }
}


int Grille::point(int x, int y)
{
    if (map[y][x] == '.') 
    {
        map[y][x] = ' ';
        return 100; // point normal
    }      

    else if (map[y][x] == 'b') 
    {
        map[y][x] = ' ';
        bonuspoint++;
        // apparition cerise après 2 gros bonus
        if (bonuspoint == 2) {
            map[15][14] = 'c'; // position de la cerise
        }
        return 500;
    }
<<<<<<< HEAD
    else if (map[y][x] == 'v') 
    {
        map[y][x] = ' ';
        bonuspoint++;        
        return 1; // vie bonus
    }
    else if (map[y][x] == 'c') 
    {
        map[y][x] = ' ';
        return 1000; // cerise
    }
    return 0;
=======
    else if (map[y][x] == '*')
    {
        map[y][x] = ' ';
    }
>>>>>>> 9142afbd7ee61ec9861e1b1d8c736fbeb8e201a8
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

// fonction pour les murs
bool Grille::isWall(int x, int y) const
{
    if (x < 0 || x >= cols() || y < 0 || y >= rows()){
        return false; // pas de mur mais hors de la grille --> on peut se tp
    }
    if (map[y][x] == '#'){
        return true; // mur donc collision
    }
    return false; // pas de mur
}