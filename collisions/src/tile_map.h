#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

#include "physics.h"

struct Tile {
    enum class Type {
        Solid,
        Air,
    } type;

    enum class Flag {
        None,
        Testing,
        Colliding,
    } flag;
};

class TileMap {
  public:
    TileMap();

    void resetFlags();
    void draw(sf::RenderWindow &window);
    Tile &tileAt(int x, int y);
    AABB tileAABB(int x, int y);

  private:
    std::vector<Tile> m_world;
    sf::RectangleShape m_tile;
};