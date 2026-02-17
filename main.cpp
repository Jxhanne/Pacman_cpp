#include <SFML/Graphics.hpp>

int main() {
    //Cr&ation de la fenêtre
    sf::RenderWindow window(sf::VideoMode({600, 600}), "Pacman");

    // Création du cercle pour Pacman 
    sf::CircleShape pacman(20.f);
    pacman.setFillColor(sf::Color::Yellow);
    pacman.setPosition({300.f, 300.f});

    float speed = 90.f; // gérer la vitesse de déplacement de Pacman 
    sf::Vector2f direction = {0.f, 0.f};

    // Horloge pour mésurer le temps entre chaque frame 
    sf::Clock clock;

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) { // On récupère les touches du claviers 
            if (event->is<sf::Event::Closed>())   // Si la croix est cliquée, on ferme la fenêtre
                window.close();
        }

        float dt = clock.restart().asSeconds(); // Le temps depuis la dernière frame 

        // On change de direction quand une touche est cliquée : les flêches ou ZQSD
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
            direction = {-speed, 0.f};
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            direction = {speed, 0.f};
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
            direction = {0.f, -speed};
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            direction = {0.f, speed};
        }

        // Avoir un mouvement fluide du Pacman 
        pacman.move(direction * dt);

        // Etape pour ce qui s'affiche dans la fenêtre : on efface tout, on redessine le pacman et on affiche le résultat à l'écran
        window.clear();
        window.draw(pacman);
        window.display();
    }

    return 0;
}