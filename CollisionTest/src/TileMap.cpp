#include "TileMap.h"

TileMap::TileMap()
{
    m_tilesVertices.reserve(401);
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            addTile(float(x * TILE_SIZE), float(y * TILE_SIZE));
        }
    }
}

void TileMap::addTile(float x, float y)
{
    sf::Vertex tl, tr, bl, br;
    tl.position = { x,              y };
    tr.position = { x + TILE_SIZE,  y };
    bl.position = { x,              y + TILE_SIZE };
    br.position = { x + TILE_SIZE,  y + TILE_SIZE };

    tl.color = sf::Color::Red;

    m_tilesVertices.push_back(tl);
    m_tilesVertices.push_back(bl);
    m_tilesVertices.push_back(br);
    m_tilesVertices.push_back(tr);
}

void TileMap::draw(sf::RenderTarget & target)
{
    target.draw(m_tilesVertices.data(), m_tilesVertices.size(), sf::Quads);
}
