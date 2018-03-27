#include "Application.h"

#include <iostream>

Application::Application()
    : m_window({ WinInfo::WIDTH, WinInfo::HEIGHT }, "Map Editor Test")
    , m_view    ({0, 0, 1366, 768})
{
    m_window.setFramerateLimit(60);
    m_spriteSheet.loadFromFile("res/tiles.png");

    for (int y = 0; y < m_spriteSheet.getSize().y / 32; y++) {
        int beginY = y * TILE_SIZE;
        for (int x = 0; x < m_spriteSheet.getSize().x / 32; x++) {
            int beginX = x * (int)TILE_SIZE;
            m_tileSectors.emplace_back(beginX, beginY, TILE_SIZE, TILE_SIZE);
        }
    }

    m_stamp.setSize({ TILE_SIZE, TILE_SIZE });

    float startPoint = 0;
    float endPoint = MAP_SIZE * TILE_SIZE;
    for (int i = 0; i < MAP_SIZE; i++) {
        sf::Vertex beginY;
        sf::Vertex endY;
        sf::Vertex beginX;
        sf::Vertex endX;
        beginY.position = { startPoint, i * TILE_SIZE };
        endY.position = { endPoint,   i *  TILE_SIZE };
        beginX.position = { i *  TILE_SIZE, startPoint };
        endX.position = { i *  TILE_SIZE, endPoint };
        m_gridLines.insert(m_gridLines.end(), { beginX, endX, beginY, endY });
    }
}

void Application::run()
{
    while (m_window.isOpen()) {
        handleEvents();
        m_window.clear();
        m_window.setView(m_view);
        

        auto pixelMousePos = sf::Mouse::getPosition(m_window);
        auto worldPosition = m_window.mapPixelToCoords(pixelMousePos);
        auto mx = worldPosition.x;
        auto my = worldPosition.y;
        
        m_stamp.setPosition({mx - (int)mx % (int)TILE_SIZE,
                             my - (int)my % (int)TILE_SIZE });
        

        m_window.draw(m_stamp);
        m_window.draw(m_gridLines.data(), m_gridLines.size(), sf::Lines);


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