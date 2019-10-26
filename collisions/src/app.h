#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>

#include "input/keyboard.h"

class Application {
  struct Tile {
    int type;
    int flag;
  };

  struct Entity {
    sf::RectangleShape sprite;
    sf::Vector2f velocity;
  };

  public:
    Application();

    void onEvent(sf::Event e);
    void onInput();
    void onUpdate();
    void onRender();

  private:
    sf::RectangleShape m_tile;
    sf::RenderWindow m_window;
    sf::Texture m_playerTexture;
    
    Keyboard m_keyboard;
    Entity m_player;
};