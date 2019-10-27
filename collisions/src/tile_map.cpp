#include "tile_map.h"

#include "common.h"

#include <cmath>
#include <iostream>

TileMap::TileMap()
    : m_world(WORLD_SIZE * WORLD_SIZE)
{
    for (int y = 0; y < WORLD_SIZE; y++) {
        for (int x = 0; x < WORLD_SIZE; x++) {
            if (x == 0 || y == 0 || x == WORLD_SIZE - 1 ||
                y == WORLD_SIZE - 1) {
                tileAt(x, y).type = Tile::Type::Solid;
            }
            else {
                if ((x > 3 || y > 3) && rand() % 100 > 80) {
                    tileAt(x, y).type = Tile::Type::Solid;
                }
                else {
                    tileAt(x, y).type = Tile::Type::Air;
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
        tile.flag = Tile::Flag::None;
    }
}

void TileMap::draw(sf::RenderWindow &window, const sf::Vector2f& cameraCenter)
{
    const int left = std::max(0, (int)(cameraCenter.x - (WIN_WIDTH / 2)) / TILE_SIZE);
    const int right = std::min(WORLD_SIZE, (int)(cameraCenter.x + (WIN_WIDTH / 2)) / TILE_SIZE) + 1;

    const int top = std::max(0, (int)(cameraCenter.y - (WIN_HEIGHT / 2)) / TILE_SIZE);
    const int bottom = std::min(WORLD_SIZE, (int)(cameraCenter.y + (WIN_HEIGHT / 2)) / TILE_SIZE) + 1;

    for (int y = top; y < bottom; y++) {
        for (int x = left; x < right; x++) {
            if (tileAt(x, y).type == Tile::Type::Air) {
                if (tileAt(x, y).flag == Tile::Flag::Testing) {
                    m_tile.setFillColor(sf::Color::Cyan);
                }
                else {
                    m_tile.setFillColor(sf::Color::Green);
                }
            }
            else {
                switch (tileAt(x, y).flag) {
                    case Tile::Flag::None:
                        m_tile.setFillColor(sf::Color::Blue);
                        break;

                    case Tile::Flag::Testing:
                        m_tile.setFillColor(sf::Color::Cyan);
                        break;

                    case Tile::Flag::Colliding:
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

AABB TileMap::tileAABB(int x, int y)
{
    return {static_cast<float>(x * TILE_SIZE),
            static_cast<float>(y * TILE_SIZE), static_cast<float>(TILE_SIZE),
            static_cast<float>(TILE_SIZE)};
}