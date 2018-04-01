#include "Application.h"

#include <iostream>

sf::RenderTexture texture;
Application::Application()
    : m_window({ 1280, 720 }, "Collide")
{
    m_window.setFramerateLimit(60);
    m_player.setSize({ 50, 100 });
    m_player.setFillColor({ 100, 255, 50 });
    m_postFXShaderTest.loadFromFile("shaders/test.vert", sf::Shader::Vertex);
    m_postFXShaderTest.loadFromFile("shaders/test.frag", sf::Shader::Fragment);
    texture.create(1280, 720);
    m_frameBuffer.setSize({ 1280, 720 });
}

void Application::run()
{
    sf::Clock clock;
    while (m_window.isOpen()) {
        checkWinEvents();
        onInput();
        onUpdate(clock.restart().asSeconds());
        m_window.clear();
        onDraw();
        m_window.display();
    }
}

void Application::checkWinEvents()
{
    sf::Event e;
    while (m_window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) {
            m_window.close();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            m_window.close();
        }
    }
}

void Application::onInput()
{
    float speed = 5;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        m_player.move(0, -speed);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        m_player.move(0, speed);
    } 

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        m_player.move(-speed, 0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        m_player.move(speed, 0);
    }
}

void Application::onUpdate(float dt)
{  
}

void Application::onDraw()
{
    texture.clear();
    texture.draw(m_player);
    texture.display();

    m_frameBuffer.setTexture(&texture.getTexture());
    m_window.draw(m_frameBuffer, &m_postFXShaderTest);
}
