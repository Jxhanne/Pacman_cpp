

 
#include <SFML/Graphics.hpp>
#include "grille.hpp"
#include <vector>

int main() {

    const int tileSize = 32;

    Grille grille(tileSize);

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(grille.cols()*tileSize, grille.rows() * tileSize)), "Pacman");

    std::vector<sf::Texture> pacmanTextures(5);

    if (!pacmanTextures[0].loadFromFile("img/1.png")) return -1;
    if (!pacmanTextures[1].loadFromFile("img/2.png")) return -1;
    if (!pacmanTextures[2].loadFromFile("img/3.png")) return -1;
    if (!pacmanTextures[3].loadFromFile("img/4.png")) return -1;
    if (!pacmanTextures[4].loadFromFile("img/5.png")) return -1;

    sf::Sprite pacman(pacmanTextures[0]);
    pacman.setPosition({300.f, 300.f});

    pacman.setScale(sf::Vector2f(
        float(tileSize) / pacmanTextures[0].getSize().x,
        float(tileSize) / pacmanTextures[0].getSize().y
    ));

    float speed = 90.f;
    sf::Vector2f direction = {0.f, 0.f};

    sf::Clock clock;
    sf::Clock animationClock;
    int frame = 0;
    float animationSpeed = 0.12f;

    while (window.isOpen()) {

        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        float dt = clock.restart().asSeconds();
        if (animationClock.getElapsedTime().asSeconds() > animationSpeed) {
            frame = (frame + 1) % 5;
            pacman.setTexture(pacmanTextures[frame]);
            animationClock.restart();
        }

    // On change de direction quand une touche est cliquée : les flêches ou ZQSD
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
        direction = {-speed, 0.f};
        pacman.setRotation(sf::degrees(180));   // Pacman regarde à gauche
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        direction = {speed, 0.f};
        pacman.setRotation(sf::degrees(0));     // Pacman regarde à droite
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
        direction = {0.f, -speed};
        pacman.setRotation(sf::degrees(270));   // Pacman regarde en haut
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        direction = {0.f, speed};
        pacman.setRotation(sf::degrees(90));    // Pacman regarde en bas
    }

        pacman.move(direction * dt);

        window.clear();
        grille.draw(window);
        window.draw(pacman);
        window.display();
    }

    return 0;
}
message.txt
3 Ko