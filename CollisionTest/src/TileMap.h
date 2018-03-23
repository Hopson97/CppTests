#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

constexpr int TILE_SIZE = 32;

class TileMap
{
    public:
        TileMap();

    private:
        void addTile(int x, int y);

        std::vector<sf::Vertex> m_tiles;
};