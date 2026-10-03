// Header file for the GameApp class

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <string>

// Owns the window and the main loop. It only decides which screen is active;
// it does not know any Tetris rules (those live in game/ later).
class GameApp {
public:
    GameApp();
    ~GameApp();

    void run();

private:
    void processEvents();
    void update();
    void render();

    void drawSky(sf::RenderTarget& target);
    void drawTitle(sf::RenderTarget& target);

    sf::RenderWindow window_;
    sf::Clock clock_;
    float skyTop_;
    float skyBottom_;
};
