#include "app.h"
#include "common.h"

Application::Application()
    : m_window({WIN_WIDTH, WIN_HEIGHT}, "Collision Testing")
{
    m_window.setFramerateLimit(60);
    m_window.setKeyRepeatEnabled(false);

    m_playerTexture.loadFromFile("res/person.png");

    m_player.sprite.setSize({PLAYER_SIZE, PLAYER_SIZE});
    m_player.sprite.setOutlineThickness(-1);
    m_player.sprite.setOutlineColor(sf::Color::White);
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
        onUpdate();
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

void Application::onInput() {}

void Application::onUpdate() {}

void Application::onRender() {}