#include "TileMap.h"

#include <iostream>

const TileType TileType::AIR    ({ 0, 0, 0, 0 }, false);
const TileType TileType::GRASS  ({ 75, 200, 25 }, true);

TileType::TileType(sf::Color color, bool canCollide)
    :   color(color)
    ,   collidable(canCollide)
{

}


TileMap::TileMap()
{
    int heights[25];

    for (int i = 0; i < 25; i++) {
        heights[i] = i / 2;
    }

    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 25; x++) {
            int h = heights[x];
            if (y > h) {
                m_tileTypes.push_back(&TileType::GRASS);
            }
            else {
                m_tileTypes.push_back(&TileType::AIR);
            }
        }
    }

    m_tilesVertices.reserve(10 * 25 * 4);
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 25; x++) {
            int i = y * 25 + x;
            if (m_tileTypes[i] != &TileType::AIR)
                addTile(float(x * TILE_SIZE), float(y * TILE_SIZE), i);
        }
    }
}

void TileMap::addTile(float x, float y, int index)
{
    sf::Vertex tl, tr, bl, br;
    tl.position = { x,              y };
    tr.position = { x + TILE_SIZE,  y };
    bl.position = { x,              y + TILE_SIZE };
    br.position = { x + TILE_SIZE,  y + TILE_SIZE };

    std::cout << index << " " << m_tileTypes.size() << std::endl;
    tl.color = m_tileTypes[index]->color;
    tr.color = m_tileTypes[index]->color;
    bl.color = m_tileTypes[index]->color;
    br.color = m_tileTypes[index]->color;

    m_tilesVertices.push_back(tl);
    m_tilesVertices.push_back(bl);
    m_tilesVertices.push_back(br);
    m_tilesVertices.push_back(tr);
}

void TileMap::draw(sf::RenderTarget & target)
{
    target.draw(m_tilesVertices.data(), m_tilesVertices.size(), sf::Quads);
}
