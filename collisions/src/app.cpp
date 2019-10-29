#include "app.h"
#include "common.h"

#include <cmath>
#include <iostream>

Application::Application()
    : m_window({WIN_WIDTH, WIN_HEIGHT}, "Collision Testing")
{
    m_camera.setSize(WIN_WIDTH, WIN_HEIGHT);
    m_window.setFramerateLimit(60);
    m_window.setKeyRepeatEnabled(false);

    m_playerTexture.loadFromFile("res/person.png");

    m_player.sprite.setOrigin({PLAYER_SIZE / 2, PLAYER_SIZE / 2});
    m_player.sprite.setSize({PLAYER_SIZE, PLAYER_SIZE});
    m_player.sprite.setOutlineThickness(-1);
    m_player.sprite.setOutlineColor(sf::Color::White);
    m_player.sprite.setTexture(&m_playerTexture);
    m_player.sprite.setPosition(TILE_SIZE * 2.5f, TILE_SIZE * 2.5f);
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
    auto mousePosition = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
    auto playerPosition = m_player.sprite.getPosition();
    auto dx = mousePosition.x - playerPosition.x;
    auto dy = mousePosition.y - playerPosition.y;
    auto rotation = std::atan2(dy, dx);

    m_player.sprite.setRotation(rotation / 3.14159 * 180 + 90);
    if (m_keyboard.isKeyDown(sf::Keyboard::W)) {
        m_player.velocity.x += std::cos(rotation) * ACCELERATION;
        m_player.velocity.y += std::sin(rotation) * ACCELERATION;
    }
    else if (m_keyboard.isKeyDown(sf::Keyboard::S)) {
        m_player.velocity.x -= std::cos(rotation) * ACCELERATION;
        m_player.velocity.y -= std::sin(rotation) * ACCELERATION;
    }
    if (m_keyboard.isKeyDown(sf::Keyboard::A)) {
        m_player.velocity.x -= std::cos(rotation + PI) * ACCELERATION;
        m_player.velocity.y -= std::sin(rotation + PI) * ACCELERATION;
    }
    else if (m_keyboard.isKeyDown(sf::Keyboard::D)) {
        m_player.velocity.x += std::cos(rotation + PI) * ACCELERATION;
        m_player.velocity.y += std::sin(rotation + PI) * ACCELERATION;
    }
}

void Application::collide(float vx, float vy)
{
    const auto &pos = m_player.sprite.getPosition();
    int minX = pos.x / TILE_SIZE;
    int minY = pos.y / TILE_SIZE;
    int maxX = (pos.x + PLAYER_SIZE) / TILE_SIZE;
    int maxY = (pos.y + PLAYER_SIZE) / TILE_SIZE;

    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {
            auto &tile = m_tileMap.tileAt(x, y);

            tile.flag = Tile::Flag::Testing;
            if (tile.type == Tile::Type::Solid) {
                tile.flag = Tile::Flag::Colliding;
                if (vx < 0) {
                    m_player.sprite.setPosition(
                        (x + 1) * TILE_SIZE + 1,
                        m_player.sprite.getPosition().y);
                }
                else if (vx > 0) {
                    m_player.sprite.setPosition(
                        x * TILE_SIZE - 1 - PLAYER_SIZE,
                        m_player.sprite.getPosition().y);
                }

                if (vy < 0) {
                    m_player.sprite.setPosition(m_player.sprite.getPosition().x,
                                                (y + 1) * TILE_SIZE + 1);
                }
                else if (vy > 0) {
                    m_player.sprite.setPosition(m_player.sprite.getPosition().x,
                                                y * TILE_SIZE - 1 -
                                                    PLAYER_SIZE);
                }
            }
        }
    }
}

void Application::onUpdate()
{
    m_tileMap.resetFlags();

    m_player.sprite.move(m_player.velocity.x, 0);
    collide(m_player.velocity.x, 0);

    m_player.sprite.move(0, m_player.velocity.y);
    collide(0, m_player.velocity.y);

    m_player.velocity *= ACC_DAMP;

    m_camera.setCenter(m_player.sprite.getPosition());
    m_window.setView(m_camera);
}

void Application::onRender()
{
    m_tileMap.draw(m_window, m_player.sprite.getPosition());

    m_window.draw(m_player.sprite);
}