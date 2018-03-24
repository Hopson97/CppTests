#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

constexpr int TILE_SIZE = 32;

struct TileType
{


    static const TileType AIR;
    static const TileType GRASS;

    sf::Color color;
    bool collidable;

    private:
        TileType(sf::Color color, bool canCollide);
};

class TileMap
{
    public:
        TileMap();
        void draw(sf::RenderTarget& target);

    private:
        void addTile(float x, float y, int index);

        std::vector<sf::Vertex> m_tilesVertices;
        std::vector<const TileType*> m_tileTypes;
};