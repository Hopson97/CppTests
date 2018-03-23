#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

constexpr int TILE_SIZE = 32;

class TileMap
{
    public:
        TileMap();
        void draw(sf::RenderTarget& target);

    private:
        void addTile(float x, float y);

        std::vector<sf::Vertex> m_tilesVertices;
        std::vector<bool> m_isTile;
};