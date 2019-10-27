#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

struct Box {
    float x;
    float y;
    float width;
    float height;
};

struct Tile {
    int type;
    int flag;
};

class TileMap {
  public:
    TileMap();

    void resetFlags();
    void draw(sf::RenderWindow &window);

    void collide(const Box& box);

    Tile &tileAt(int x, int y);

  private:
    std::vector<Tile> m_world;
    sf::RectangleShape m_tile;
};