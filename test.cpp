#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    std::cout << "Test SFML OK\n";

    sf::RenderWindow window(sf::VideoMode({400, 400}), "SFML Test");
    sf::CircleShape circle(150.f);
    circle.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}