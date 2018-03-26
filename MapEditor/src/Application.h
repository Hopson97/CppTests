#pragma once

#include <SFML/Graphics.hpp>

namespace WinInfo
{
    constexpr unsigned WIDTH = 1366;
    constexpr unsigned HEIGHT = 768;
}

constexpr unsigned TILE_SIZE = 32;

class Application
{
    public:
        Application();

        void run();

    private:
        void handleEvents();

        sf::RenderWindow m_window;
        sf::Texture m_spriteSheet;
        sf::RectangleShape m_tile;

        std::vector<sf::IntRect> m_tileSectors;
        std::vector<sf::RectangleShape> temp;
};