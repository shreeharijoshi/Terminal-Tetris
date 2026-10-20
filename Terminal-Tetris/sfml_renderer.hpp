#pragma once

#include <SFML/Graphics.hpp>
#include "renderer.hpp"
#include "gameBoard.hpp"
#include "tetromino.hpp"
#include "score.hpp"

class SFMLRenderer : public Renderer {
public:
    SFMLRenderer();
    void render(const gameBoard& board,
                const Tetromino& activePiece,
                const Tetromino& nextPiece,
                const Score& score) override;
    void renderGameOver(const Score& score) override;
    void renderControls() override;
    void renderMenu();
private:
    sf::RenderWindow window;
    const int blockSize = 40; // pixels per block
    const int boardWidth = 10; // blocks
    const int boardHeight = 20; // blocks
    sf::Color blockColor = sf::Color::Green;
    sf::Color gridColor = sf::Color(50, 50, 50);
    sf::Font font;
    void drawBoard(const gameBoard& board);
    void drawPiece(const Tetromino& piece, const sf::Vector2i& offset);
};
