#include "Application.h"

#include <iostream>

Application::Application()
    : m_window({ 1280, 720 }, "Collide")
{
    m_window.setFramerateLimit(60);

    
    m_player.rect.setSize({ 32, 32 });
    m_player.rect.setFillColor(sf::Color::Blue);
    m_player.rect.setPosition(500, 100);
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
    static int n = 0;

    int px = m_player.rect.getPosition().x / TILE_SIZE;
    int py = m_player.rect.getPosition().y / TILE_SIZE;

    for (int y = -1; y <= 1; y++) {
        for (int x = 1; x <= 1; x++) {
            auto& tile = m_tileMap.getTile(x + px, y + py);
            if (&tile == &TileType::GRASS) {
                sf::FloatRect rect;
                rect.left = (x + px) * TILE_SIZE;
                rect.top  = (y + py) * TILE_SIZE;
                rect.width = TILE_SIZE; 
                rect.height = TILE_SIZE;
                if (m_player.rect.getGlobalBounds().intersects(rect)) {
                    std::cout << n++ << " Collide af\n";
                }
            }
        }
    }

    int x = m_player.rect.getPosition().x / TILE_SIZE;
    int y = m_player.rect.getPosition().y / TILE_SIZE;

    auto& tile = m_tileMap.getTile(x, y);
    if (&tile == &TileType::GRASS) {
        std::cout << "Collide\n";
    }
}

void Application::onDraw()
{
    m_tileMap.draw(m_window);

    m_window.draw(m_player.rect);
}
