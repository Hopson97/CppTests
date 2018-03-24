#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

constexpr int TILE_SIZE = 32;

constexpr int WIDTH = 1280 / TILE_SIZE;
constexpr int HEIGHT = 720 / TILE_SIZE;

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

        const TileType& getTile(int x, int y) const;

    private:
        void addTile(float x, float y, int index);

        std::vector<sf::Vertex> m_tilesVertices;
        std::vector<const TileType*> m_tileTypes;
};