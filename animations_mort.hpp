#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

void jouerAnimationMort(sf::RenderWindow& window,
                        sf::Sprite& pacman,
                        const std::vector<sf::Texture>& mortTextures,
                        float frameTime = 0.08f);