#ifndef GAME_HPP
#define GAME_HPP
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Game {
private:
    sf::RenderWindow& window;
    std::vector<std::unique_ptr<Entity>> platforms; // Platforms and walls
    std::vector<std::unique_ptr<Entity>> rifts; // Dimensional rifts
    std::unique_ptr<Entity> player;
    std::unique_ptr<Entity> exit;
    sf::Vector2i cursorPos;
    bool isExitReached;

public:
    Game(sf::RenderWindow& win);
    void handleEvents();
    void update(float deltaTime);
    void render();
};

#endif // GAME_HPP
