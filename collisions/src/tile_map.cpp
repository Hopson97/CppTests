#include "tile_map.h"

#include "common.h"

TileMap::TileMap()
:   m_world(WORLD_SIZE * WORLD_SIZE)
{
    for (int y = 0; y < WORLD_SIZE; y++) {
        for (int x = 0; x < WORLD_SIZE; x++) {
            if (x == 0 || y == 0 || x == WORLD_SIZE - 1 ||
                y == WORLD_SIZE - 1) {
                tileAt(x, y).type = 1;
            }
            else {
                if ((x > 3 || y > 3) && rand() % 100 > 80) {
                    tileAt(x, y).type = 1;
                }
                else {
                    tileAt(x, y).type = 0;
                }
            }
        }
    }

    m_tile.setSize({TILE_SIZE, TILE_SIZE});
    m_tile.setOutlineThickness(-1);
    m_tile.setOutlineColor(sf::Color::Black);
}

void TileMap::resetFlags()
{
    for (auto &tile : m_world) {
        tile.flag = 0;
    }
}

void TileMap::draw(sf::RenderWindow &window)
{
    for (int y = 0; y < WORLD_SIZE; y++) {
        for (int x = 0; x < WORLD_SIZE; x++) {
            if (tileAt(x, y).type == 0) {
                m_tile.setFillColor(sf::Color::Green);
            }
            else {
                int flag = tileAt(x, y).flag;
                switch (flag) {
                    case 0:
                        m_tile.setFillColor(sf::Color::Blue);
                        break;

                    case 1:
                        m_tile.setFillColor(sf::Color::Cyan);
                        break;

                    case 2:
                        m_tile.setFillColor(sf::Color::Red);
                        break;

                    default:
                        break;
                }
            }
            m_tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            window.draw(m_tile);
        }
    }
}

Tile &TileMap::tileAt(int x, int y) { return m_world[y * WORLD_SIZE + x]; }