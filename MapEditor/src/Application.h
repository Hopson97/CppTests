#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>

namespace WinInfo
{
    constexpr unsigned WIDTH = 1366;
    constexpr unsigned HEIGHT = 768;
}

constexpr float TILE_SIZE = 32;
constexpr unsigned MAP_SIZE = 64;

class Application
{
    public:
        Application();

        void run();

    private:
        void handleEvents();

        std::array<int, MAP_SIZE * MAP_SIZE> m_tileMap;
        std::vector<sf::Vertex> m_gridLines;

        sf::RenderWindow m_window;
        sf::Texture m_spriteSheet;

        std::vector<sf::IntRect> m_tileSectors;

        sf::RectangleShape m_stamp;
};