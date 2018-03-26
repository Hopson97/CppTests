#include "Application.h"

#include <iostream>

Application::Application()
    : m_window({ WinInfo::WIDTH, WinInfo::HEIGHT }, "Map Editor Test")
{
    m_window.setFramerateLimit(60);
    m_spriteSheet.loadFromFile("res/tiles.png");

    int i = 0;
    for (int y = 0; y < m_spriteSheet.getSize().y / 32; y++) {
        int beginY = y * TILE_SIZE;
        for (int x = 0; x < m_spriteSheet.getSize().x / 32; x++) {
            int beginX = x * TILE_SIZE;

            m_tileSectors.emplace_back(beginX, beginY, TILE_SIZE, TILE_SIZE);
            temp.emplace_back(sf::Vector2f{ (float)TILE_SIZE, (float)TILE_SIZE });
            temp.back().setPosition(beginX + (x * 10), beginY + (y * 10));
            temp.back().setTexture(&m_spriteSheet);
            temp.back().setTextureRect(m_tileSectors.back());
        }
    }

    

    std::cout << i << std::endl;
}

void Application::run()
{
    while (m_window.isOpen()) {
        handleEvents();

        m_window.clear();

        for (auto& rect : temp) {
            m_window.draw(rect);
        }

        m_window.display();
    }
}

void Application::handleEvents()
{
    sf::Event e;
    while (m_window.pollEvent(e)) {
        switch (e.type) {
            case sf::Event::Closed:
                m_window.close();
        }
    }
}