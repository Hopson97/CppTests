#include "input/keyboard.h"
#include <SFML/Graphics.hpp>
#include <ctime>
#include <vector>

#include "app.h"

constexpr int WOLRD_SIZE = 16;
constexpr int TILE_SIZE = 32;
constexpr int PLAYER_SIZE = TILE_SIZE - 5;

constexpr int WIN_WIDTH = TILE_SIZE * WOLRD_SIZE + 50;
constexpr int WIN_HEIGHT = TILE_SIZE * WOLRD_SIZE + 20;

auto index(int x, int y) { return y * WOLRD_SIZE + x; }

struct Tile {
    int type;
    int flag;
};

auto createWorld()
{
    std::vector<Tile> world(WOLRD_SIZE * WOLRD_SIZE);

    for (int y = 0; y < WOLRD_SIZE; y++) {
        for (int x = 0; x < WOLRD_SIZE; x++) {
            if (x == 0 || y == 0 || x == WOLRD_SIZE - 1 ||
                y == WOLRD_SIZE - 1) {
                world[index(x, y)].type = 1;
            }
            else {
                if ((x > 3 || y > 3) && rand() % 100 > 80) {
                    world[index(x, y)].type = 1;
                }
                else {
                    world[index(x, y)].type = 0;
                }
            }
        }
    }
    return world;
}

int main()
{
    Application app;
    app.run();
    return 0;

    std::srand(std::time(nullptr));
    sf::RenderWindow window({WIN_WIDTH, WIN_HEIGHT}, "SFML",
                            sf::Style::Default);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    sf::RectangleShape playerSprite;
    playerSprite.setSize({PLAYER_SIZE, PLAYER_SIZE});
    playerSprite.setOutlineThickness(-1);
    playerSprite.setOutlineColor(sf::Color::White);

    sf::Texture playerTexture;
    playerTexture.loadFromFile("res/person.png");
    playerSprite.setTexture(&playerTexture);

    playerSprite.setPosition(100, 100);

    sf::RectangleShape tileSprite;
    tileSprite.setSize({TILE_SIZE, TILE_SIZE});
    tileSprite.setOutlineThickness(-1);
    tileSprite.setOutlineColor(sf::Color::Black);

    Keyboard keyboard;

    auto world = createWorld();

    const float acceleration = 0.4f;
    sf::Vector2f velocity;

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            keyboard.update(e);
            switch (e.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }

        if (keyboard.isKeyDown(sf::Keyboard::W)) {
            velocity.y -= acceleration;
        }
        else if (keyboard.isKeyDown(sf::Keyboard::S)) {
            velocity.y += acceleration;
        }
        if (keyboard.isKeyDown(sf::Keyboard::A)) {
            velocity.x -= acceleration;
        }
        if (keyboard.isKeyDown(sf::Keyboard::D)) {
            velocity.x += acceleration;
        }

        for (auto &tile : world) {
            tile.flag = 0;
        }

        velocity *= 0.8f;

        auto pos = playerSprite.getPosition() + velocity;
        int tileX = pos.x / TILE_SIZE;
        int tileY = pos.y / TILE_SIZE;
        bool collidex = false;
        bool collidey = false;
        for (int y = -1; y <= 1; y++) {
            for (int x = -1; x <= 1; x++) {
                int newTileX = tileX + x;
                int newTileY = tileY + y;
                auto &tile = world[index(newTileX, newTileY)];
                if (tile.type == 1) {
                    tile.flag = 1;
                    float tileX = newTileX * TILE_SIZE;
                    float tileY = newTileY * TILE_SIZE;
                    if (pos.x <= tileX + TILE_SIZE &&
                        pos.y <= tileY + TILE_SIZE &&
                        pos.x + PLAYER_SIZE >= tileX &&
                        pos.y + PLAYER_SIZE >= tileY) {
                        if (pos.x <= tileX + TILE_SIZE &&
                            pos.x + PLAYER_SIZE >= tileX) {
                            tile.flag = 2;
                            collidex = true;
                        }
                        if (pos.y + PLAYER_SIZE >= tileY &&
                            pos.y <= tileY + TILE_SIZE) {
                            tile.flag = 2;
                            collidey = true;
                        }
                    }
                }
            }
        }

        if (!collidex) {
            playerSprite.move(velocity.x, 0);
        }
        if (!collidey) {
            playerSprite.move(0, velocity.y);
        }

        window.clear();

        for (int y = 0; y < WOLRD_SIZE; y++) {
            for (int x = 0; x < WOLRD_SIZE; x++) {
                if (world[index(x, y)].type == 0) {
                    tileSprite.setFillColor(world[index(x, y)].flag
                                                ? sf::Color::Cyan
                                                : sf::Color::Green);
                }
                else {
                    int flag = world[index(x, y)].flag;
                    switch (flag) {
                        case 0:
                            tileSprite.setFillColor(sf::Color::Blue);
                            break;

                        case 1:
                            tileSprite.setFillColor(sf::Color::Cyan);
                            break;

                        case 2:
                            tileSprite.setFillColor(sf::Color::Red);
                            break;

                        default:
                            break;
                    }
                }
                tileSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                window.draw(tileSprite);
            }
        }

        window.draw(playerSprite);

        window.display();
    }
}
