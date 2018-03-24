#include "Application.h"

#include <iostream>

Application::Application()
    : m_window({ 1280, 720 }, "Collide")
{
    m_window.setFramerateLimit(60);
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
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            m_window.close();
        }
    }
}

void Application::onInput()
{
    m_player.input();
}

void Application::onUpdate()
{
    static int n = 1;
    m_player.update();
    auto position = m_player.getPosition();
    auto boxSize  = m_player.getBoxSize();

   
    
    int px = int(position.x / TILE_SIZE);
    int py = int(position.y / TILE_SIZE);

    for (int y = -boxSize.y; y <= boxSize.y; y++) {
        for (int x = -boxSize.x; x <= boxSize.x; x++) {
            auto& tile = m_tileMap.getTile(x + px, y + py);
            if (&tile == &TileType::GRASS) {
                sf::FloatRect tileRect;
                tileRect.left = (x + px) * TILE_SIZE;
                tileRect.top  = (y + py) * TILE_SIZE;
                tileRect.width = TILE_SIZE;
                tileRect.height = TILE_SIZE;

                sf::FloatRect playerRect;
                playerRect.left = position.x;
                playerRect.top = position.y;
                playerRect.width = boxSize.x * TILE_SIZE;
                playerRect.height = boxSize.y * TILE_SIZE;

                if (playerRect.intersects(tileRect)) {
                    std::cout << n++ << " Collide af\n";
                }
            }
        }
    }
}

void Application::onDraw()
{
    m_tileMap.draw(m_window);

    m_player.draw(m_window);
}
