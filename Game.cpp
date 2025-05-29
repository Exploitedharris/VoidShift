#include "Game.hpp"
#include <cmath>

class Player : public Entity {
private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    sf::Vector2f velocity;
    bool active;
    bool isGrounded;

public:
    Player(float x, float y) : position(x, y), velocity(0.f, 0.f), active(true), isGrounded(false) {
        shape.setSize(sf::Vector2f(20.f, 20.f));
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {
        velocity.y += 500.f * deltaTime; // Gravity
        position += velocity * deltaTime;
        if (position.y > 500.f) {
            position.y = 500.f;
            velocity.y = 0.f;
            isGrounded = true;
        }
        shape.setPosition(position);
    }

    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }

    sf::Vector2f getPosition() const override { return position; }
    void setPosition(const sf::Vector2f& pos) override { position = pos; shape.setPosition(pos); }
    bool isActive() const override { return active; }
    void shift(float dx, float dy) override {} // Player not affected by shifts
    void jump() { if (isGrounded) { velocity.y = -300.f; isGrounded = false; } }
    void move(float dx) { velocity.x = dx; }
};

class Platform : public Entity {
private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    bool active;

public:
    Platform(float x, float y, float w, float h) : position(x, y), active(true) {
        shape.setSize(sf::Vector2f(w, h));
        shape.setFillColor(sf::Color::Gray);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {}
    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }

    sf::Vector2f getPosition() const override { return position; }
    void setPosition(const sf::Vector2f& pos) override { position = pos; shape.setPosition(pos); }
    bool isActive() const override { return active; }
    void shift(float dx, float dy) override { position.x += dx; position.y += dy; shape.setPosition(position); }
    sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }
};

class Rift : public Entity {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    bool active;

public:
    Rift(float x, float y) : position(x, y), active(true) {
        shape.setRadius(10.f);
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {}
    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }

    sf::Vector2f getPosition() const override { return position; }
    void setPosition(const sf::Vector2f& pos) override { position = pos; shape.setPosition(pos); }
    bool isActive() const override { return active; }
    void shift(float dx, float dy) override {} // Rifts not affected
};

class Exit : public Entity {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    bool active;

public:
    Exit(float x, float y) : position(x, y), active(true) {
        shape.setRadius(10.f);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {}
    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }

    sf::Vector2f getPosition() const override { return position; }
    void setPosition(const sf::Vector2f& pos) override { position = pos; shape.setPosition(pos); }
    bool isActive() const override { return active; }
    void shift(float dx, float dy) override {} // Exit not affected
};

Game::Game(sf::RenderWindow& win) : window(win), cursorPos(0, 0), isExitReached(false) {
    player = std::make_unique<Player>(200.f, 400.f);
    platforms.push_back(std::make_unique<Platform>(150.f, 500.f, 500.f, 50.f)); // Ground
    platforms.push_back(std::make_unique<Platform>(400.f, 400.f, 100.f, 20.f)); // Floating platform
    platforms.push_back(std::make_unique<Platform>(300.f, 300.f, 100.f, 20.f)); // Another platform
    exit = std::make_unique<Exit>(450.f, 280.f);
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::R) {
                player->setPosition(sf::Vector2f(200.f, 400.f));
                platforms.clear();
                rifts.clear();
                platforms.push_back(std::make_unique<Platform>(150.f, 500.f, 500.f, 50.f));
                platforms.push_back(std::make_unique<Platform>(400.f, 400.f, 100.f, 20.f));
                platforms.push_back(std::make_unique<Platform>(300.f, 300.f, 100.f, 20.f));
                exit = std::make_unique<Exit>(450.f, 280.f);
                cursorPos = {0, 0};
                isExitReached = false;
            } else if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            } else if (event.key.code == sf::Keyboard::W) {
                dynamic_cast<Player&>(*player).jump();
            } else if (event.key.code == sf::Keyboard::Up && cursorPos.y > 0) {
                cursorPos.y--;
            } else if (event.key.code == sf::Keyboard::Down && cursorPos.y < 9) {
                cursorPos.y++;
            } else if (event.key.code == sf::Keyboard::Left && cursorPos.x > 0) {
                cursorPos.x--;
            } else if (event.key.code == sf::Keyboard::Right && cursorPos.x < 15) {
                cursorPos.x++;
            } else if (event.key.code == sf::Keyboard::Space) {
                rifts.push_back(std::make_unique<Rift>(150.f + cursorPos.x * 40.f, 100.f + cursorPos.y * 40.f));
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        dynamic_cast<Player&>(*player).move(-100.f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        dynamic_cast<Player&>(*player).move(100.f);
    } else {
        dynamic_cast<Player&>(*player).move(0.f);
    }
}

void Game::update(float deltaTime) {
    player->update(deltaTime);
    for (auto& platform : platforms) {
        platform->update(deltaTime);
    }
    for (auto& rift : rifts) {
        rift->update(deltaTime);
    }
    exit->update(deltaTime);

    // Collision detection
    sf::FloatRect playerBounds = sf::FloatRect(player->getPosition(), sf::Vector2f(20.f, 20.f));
    for (const auto& platform : platforms) {
        if (playerBounds.intersects(platform->getBounds()) && player->getPosition().y + 20.f <= platform->getBounds().top + 5.f) {
            player->setPosition({player->getPosition().x, platform->getBounds().top - 20.f});
            dynamic_cast<Player&>(*player).jump(); // Reset velocity
            dynamic_cast<Player&>(*player).isGrounded = true;
        }
    }

    // Rift effects
    for (const auto& rift : rifts) {
        if (rift->isActive()) {
            sf::Vector2f riftPos = rift->getPosition();
            for (auto& platform : platforms) {
                float dist = std::hypot(riftPos.x - platform->getPosition().x, riftPos.y - platform->getPosition().y);
                if (dist < 100.f) {
                    platform->shift(50.f * deltaTime, 0.f); // Shift platforms right
                }
            }
        }
    }

    // Check exit
    if (std::hypot(player->getPosition().x - exit->getPosition().x, player->getPosition().y - exit->getPosition().y) < 20.f) {
        isExitReached = true;
    }
}

void Game::render() {
    window.clear(sf::Color::Black);

    // Draw platforms
    for (const auto& platform : platforms) {
        platform->render(window);
    }

    // Draw rifts
    for (const auto& rift : rifts) {
        rift->render(window);
    }

    // Draw exit
    exit->render(window);

    // Draw cursor
    sf::RectangleShape cursor(sf::Vector2f(40.f, 40.f));
    cursor.setFillColor(sf::Color::Transparent);
    cursor.setOutlineColor(sf::Color::Yellow);
    cursor.setOutlineThickness(2.f);
    cursor.setPosition(150.f + cursorPos.x * 40.f, 100.f + cursorPos.y * 40.f);
    window.draw(cursor);

    // Draw player
    player->render(window);

    // Draw win condition
    if (isExitReached) {
        sf::Text winText;
        winText.setString("Level Complete!");
        winText.setCharacterSize(24);
        winText.setFillColor(sf::Color::Green);
        winText.setPosition(300.f, 400.f);
        window.draw(winText);
    }

    window.display();
}
