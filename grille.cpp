// include pour l'affichage
#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include <string>
// autre
#include <iostream>


int main()
{
  const int tileSize = 32;
  

  std::vector<std::string> map = { // plateau de jeu 
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
  int rows = map.size(); // ligne
  int cols = map[0].size(); // colonne
  std::cout << "Rows: " << rows << std::endl;
  std::cout << "Cols: " << cols << std::endl;

  // création de la window
  sf::RenderWindow window(
    sf::VideoMode(sf::Vector2u(cols * tileSize, rows * tileSize)),
    "Pacman"
  );

  // créartion du mur 
  sf::RectangleShape wall(sf::Vector2f((float)tileSize, (float)tileSize));
  wall.setFillColor(sf::Color::Blue);
  // création point
  sf::CircleShape nourriture (tileSize * 0.12f); //0.12f a revoir pour crée la bonne taille de point
  nourriture.setFillColor(sf::Color::White);
  nourriture.setOrigin({nourriture.getRadius(), nourriture.getRadius()}); //utile pour centrer dans la case les points

  // boucle de window ouverte
  while (window.isOpen()){


    while (auto ev = window.pollEvent()){
        const sf::Event& e = *ev;
        if (e.is<sf::Event::Closed>())
            window.close();
    }

    window.clear();

    // TODO: boucles y/x ici
    // if (c == '#') { wall.setPosition({px, py}); window.draw(wall); }
    for (int y = 0; y < rows; ++y){ // on parcours chaque ligne

      for (int x = 0; x < cols; ++x){ // et chaque case dans la ligne

          char c = map[y][x]; // c revient à la case précise (coordonéées de rows et de col)
          sf::Vector2f pos{ x * (float)tileSize, y * (float)tileSize };// calcule la position lié a la tilesize

          //float px = x * (float)tileSize;
          //float py = y * (float)tileSize;
          if (c == '#'){
            wall.setPosition(pos); 
            window.draw(wall);
          }

          else if (c == '.'){
            float r = nourriture.getRadius();
            nourriture.setPosition({pos.x + tileSize/2.f, pos.y + tileSize/2.f}); // centrer le point
            window.draw(nourriture);
          }

      }
    }

    window.display();
}

return 0;


}
