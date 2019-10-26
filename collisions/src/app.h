#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>

#include "input/keyboard.h"

class Application {
    struct Entity {
        sf::RectangleShape sprite;
        sf::Vector2f velocity;
    };

  public:
    struct Tile {
        int type;
        int flag;
    };
    Application();

    void run();

  private:
    void onEvent(sf::Event e);
    void onInput();
    void onUpdate();
    void onRender();

    sf::RectangleShape m_tile;
    sf::RenderWindow m_window;
    sf::Texture m_playerTexture;

    Keyboard m_keyboard;
    Entity m_player;

    std::vector<Tile> m_world;
};