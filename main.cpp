#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    try {
        // Initialize window
        sf::RenderWindow window(sf::VideoMode(800, 600), "VoidShift", sf::Style::Close);
        window.setFramerateLimit(60);

        // Create game instance
        Game game(window);

        // Main loop
        sf::Clock clock;
        while (window.isOpen()) {
            sf::Time deltaTime = clock.restart();
            game.handleEvents();
            game.update(deltaTime.asSeconds());
            game.render();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
