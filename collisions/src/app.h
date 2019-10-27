#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "input/keyboard.h"
#include "tile_map.h"

class Application {
    struct Entity {
        AABB aabb;
        sf::RectangleShape body;
        sf::RectangleShape sprite;
        sf::Vector2f velocity;
    };

  public:
    Application();

    void run();

  private:
    void onEvent(sf::Event e);
    void onInput();
    void onUpdate();
    void onRender();

    void collide(float vx, float vy);

    sf::RenderWindow m_window;
    sf::Texture m_playerTexture;

    Keyboard m_keyboard;
    Entity m_player;
    TileMap m_tileMap;
};