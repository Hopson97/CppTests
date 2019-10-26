#include "app.h"
#include "common.h"

#include <cmath>
#include <iostream>

namespace {
    auto index(int x, int y) { return y * WORLD_SIZE + x; }

    auto createWorld()
    {
        std::vector<Application::Tile> world(WORLD_SIZE * WORLD_SIZE);

        for (int y = 0; y < WORLD_SIZE; y++) {
            for (int x = 0; x < WORLD_SIZE; x++) {
                if (x == 0 || y == 0 || x == WORLD_SIZE - 1 ||
                    y == WORLD_SIZE - 1) {
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
} // namespace

Application::Application()
    : m_window({WIN_WIDTH, WIN_HEIGHT}, "Collision Testing")
    , m_world(createWorld())
{
    m_window.setFramerateLimit(60);
    m_window.setKeyRepeatEnabled(false);

    m_playerTexture.loadFromFile("res/person.png");

    m_player.sprite.setSize({PLAYER_SIZE, PLAYER_SIZE});
    m_player.sprite.setOutlineThickness(-1);
    m_player.sprite.setOutlineColor(sf::Color::White);
    m_player.sprite.setOrigin({PLAYER_SIZE / 2, PLAYER_SIZE / 2});
    m_player.sprite.setTexture(&m_playerTexture);
    m_player.sprite.setPosition(TILE_SIZE * 2.5f, TILE_SIZE * 2.5f);

    m_tile.setSize({TILE_SIZE, TILE_SIZE});
    m_tile.setOutlineThickness(-1);
    m_tile.setOutlineColor(sf::Color::Black);
}

void Application::run()
{
    while (m_window.isOpen()) {
        sf::Event e;
        while (m_window.pollEvent(e)) {
            onEvent(e);
        }

        onInput();

        onUpdate();

        m_window.clear();
        onRender();
        m_window.display();
    }
}

void Application::onEvent(sf::Event e)
{
    m_keyboard.update(e);
    switch (e.type) {
        case sf::Event::Closed:
            m_window.close();
            break;

        default:
            break;
    }
}

void Application::onInput()
{
    auto mousePosition = sf::Mouse::getPosition(m_window);
    auto playerPosition = m_player.sprite.getPosition();
    auto dx = mousePosition.x - playerPosition.x;
    auto dy = mousePosition.y - playerPosition.y;
    auto rotation = std::atan2(dy, dx);

    m_player.sprite.setRotation(rotation * 180 / PI + 90);

    if (m_keyboard.isKeyDown(sf::Keyboard::W)) {
        auto rads = (m_player.sprite.getRotation() + 90) * PI / 180;
        m_player.velocity.x -= std::cos(rads) * ACCELERATION;
        m_player.velocity.y -= std::sin(rads) * ACCELERATION;
    }
    else if (m_keyboard.isKeyDown(sf::Keyboard::S)) {
        auto rads = (m_player.sprite.getRotation() + 90) * PI / 180;
        m_player.velocity.x += std::cos(rads) * ACCELERATION;
        m_player.velocity.y += std::sin(rads) * ACCELERATION;
    }

    if (m_keyboard.isKeyDown(sf::Keyboard::A)) {
        auto rads = (m_player.sprite.getRotation()) * PI / 180;
        m_player.velocity.x -= std::cos(rads) * ACCELERATION;
        m_player.velocity.y -= std::sin(rads) * ACCELERATION;
    }
    else if (m_keyboard.isKeyDown(sf::Keyboard::D)) {
        auto rads = (m_player.sprite.getRotation()) * PI / 180;
        m_player.velocity.x += std::cos(rads) * ACCELERATION;
        m_player.velocity.y += std::sin(rads) * ACCELERATION;
    }
}

void Application::onUpdate()
{
    //Reset tile states
    for (auto& tile : m_world) {
        tile.flag = 0;
    }

    auto pos = m_player.sprite.getPosition() + m_player.velocity;
    pos.x -= PLAYER_SIZE / 2;
    pos.y -= PLAYER_SIZE / 2;
    int tileX = pos.x / TILE_SIZE;
    int tileY = pos.y / TILE_SIZE;
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            int newTileX = tileX + x;
            int newTileY = tileY + y;
            auto &tile = m_world[index(newTileX, newTileY)];
            if (tile.type == 1) {
                tile.flag = 1;
                float tileX = newTileX * TILE_SIZE;
                float tileY = newTileY * TILE_SIZE;
                if (pos.x <= tileX + TILE_SIZE && pos.y <= tileY + TILE_SIZE &&
                    pos.x + PLAYER_SIZE >= tileX &&
                    pos.y + PLAYER_SIZE >= tileY) {
                    if (pos.x <= tileX + TILE_SIZE &&
                        pos.x + PLAYER_SIZE >= tileX) {
                        tile.flag = 2;
                    }
                    if (pos.y + PLAYER_SIZE >= tileY &&
                        pos.y <= tileY + TILE_SIZE) {
                        tile.flag = 2;
                    }
                }
            }
        }
    }

        m_player.sprite.move(m_player.velocity);
    m_player.velocity *= ACC_DAMP;

}

void Application::onRender()
{
    for (int y = 0; y < WORLD_SIZE; y++) {
        for (int x = 0; x < WORLD_SIZE; x++) {
            if (m_world[index(x, y)].type == 0) {
                m_tile.setFillColor(sf::Color::Green);
            }
            else {
                int flag = m_world[index(x, y)].flag;
                switch (flag) {
                    case 0:
                        m_tile.setFillColor(sf::Color::Blue);
                        break;

                    case 1:
                        m_tile.setFillColor(sf::Color::Cyan);
                        break;

                    case 2:
                        m_tile.setFillColor(sf::Color::Red);
                        break;

                    default:
                        break;
                }
            }
            m_tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            m_window.draw(m_tile);
        }

        m_window.draw(m_player.sprite);
    }
}