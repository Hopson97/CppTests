#include "app.h"
#include "common.h"

#include <cmath>
#include <iostream>

Application::Application()
    : m_window({WIN_WIDTH, WIN_HEIGHT}, "Collision Testing")
{
    m_window.setFramerateLimit(60);
    m_window.setKeyRepeatEnabled(false);

    m_playerTexture.loadFromFile("res/person.png");

    m_player.sprite.setSize({PLAYER_SIZE, PLAYER_SIZE});
    m_player.body.setSize({PLAYER_SIZE, PLAYER_SIZE});
    m_player.body.setOutlineThickness(2);
    m_player.body.setOutlineColor(sf::Color::White);
    m_player.body.setFillColor(sf::Color::Transparent);
    m_player.sprite.setOrigin({PLAYER_SIZE / 2, PLAYER_SIZE / 2});
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
    m_tileMap.resetFlags();
    m_player.sprite.move(m_player.velocity.x, 0);
    m_player.sprite.move(0, m_player.velocity.y);

    m_player.velocity *= ACC_DAMP;
}

void Application::onRender()
{
    m_tileMap.draw(m_window);

    m_player.body.setPosition(m_player.sprite.getPosition().x - PLAYER_SIZE / 2,
                              m_player.sprite.getPosition().y -
                                  PLAYER_SIZE / 2);
    m_window.draw(m_player.sprite);
    m_window.draw(m_player.body);
}