#include "TileMap.h"

#include <iostream>

const TileType TileType::AIR    ({ 0, 0, 0, 0 }, false);
const TileType TileType::GRASS  ({ 75, 200, 25 }, true);

TileType::TileType(sf::Color color, bool canCollide)
    :   color(color)
    ,   collidable(canCollide)
{}


TileMap::TileMap()
{
    std::vector<int> heights;

    

    for (int i = -10; i < WIDTH - 10; i++) {
        heights.push_back(abs(i / 2));
    }

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int h = heights[x];
            if (y > h) {
                m_tileTypes.push_back(&TileType::GRASS);
            }
            else {
                m_tileTypes.push_back(&TileType::AIR);
            }
        }
    }

    m_tilesVertices.reserve(HEIGHT * WIDTH * 4);
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int i = y * WIDTH + x;
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

const TileType & TileMap::getTile(int x, int y) const
{
    try {
        return *m_tileTypes.at(y * WIDTH + x);
    }
    catch (std::out_of_range& e) {
        return TileType::AIR;
    }
}
