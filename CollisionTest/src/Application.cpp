#include "Application.h"

Application::Application()
    : m_window({ 1280, 720 }, "Collide")
{
    m_window.setFramerateLimit(60);

    m_player.rect.setSize({ 32, 32 });
    m_player.rect.setFillColor(sf::Color::Blue);
}

void Application::run()
{
    while (m_window.isOpen()) {
        checkWinEvents();
        onInput();
        onUpdate();
        m_window.clear();
        onDraw();
        m_window.display();
    }
}

void Application::checkWinEvents()
{
    sf::Event e;
    while (m_window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) {
            m_window.close();
        }
    }
}

void Application::onInput()
{
    float speed = 0.25;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        m_player.velocity.y -= speed;
    } 
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        m_player.velocity.y += speed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        m_player.velocity.x -= speed;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        m_player.velocity.x += speed;
    }
}

void Application::onUpdate()
{
    m_player.rect.move(m_player.velocity);
    m_player.velocity *= 0.99f;
}

void Application::onDraw()
{
    m_tileMap.draw(m_window);

    m_window.draw(m_player.rect);
}
