#include "sfml_renderer.hpp"
#include <iostream>

SFMLRenderer::SFMLRenderer() {
    // Create a window sized for board + side panels
    int width = boardWidth * blockSize + 200; // extra space for next piece and stats
    int height = boardHeight * blockSize + 40;
    window.create(sf::VideoMode(width, height), "Tetris", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    // Load a font for UI text
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Failed to load font, UI text may not render correctly." << std::endl;
    }
}

void SFMLRenderer::drawBoard(const gameBoard& board) {
    // Draw locked cells
    for (const coords& cell : board.used_spaces) {
        sf::RectangleShape rect(sf::Vector2f(blockSize - 1, blockSize - 1));
        rect.setFillColor(blockColor);
        rect.setPosition(cell.x * blockSize, cell.y * blockSize);
        window.draw(rect);
    }
    // Draw grid lines (optional subtle grid)
    sf::Vertex line[2];
    line[0].color = gridColor;
    line[1].color = gridColor;
    // vertical lines
    for (int x = 0; x <= boardWidth; ++x) {
        line[0].position = sf::Vector2f(x * blockSize, 0);
        line[1].position = sf::Vector2f(x * blockSize, boardHeight * blockSize);
        window.draw(line, 2, sf::Lines);
    }
    // horizontal lines
    for (int y = 0; y <= boardHeight; ++y) {
        line[0].position = sf::Vector2f(0, y * blockSize);
        line[1].position = sf::Vector2f(boardWidth * blockSize, y * blockSize);
        window.draw(line, 2, sf::Lines);
    }
}

void SFMLRenderer::drawPiece(const Tetromino& piece, const sf::Vector2i& offset) {
    const coords* pieceCoords = piece.getCoords();
    for (int i = 0; i < 4; ++i) {
        sf::RectangleShape rect(sf::Vector2f(blockSize - 1, blockSize - 1));
        rect.setFillColor(blockColor);
        int x = offset.x + pieceCoords[i].x;
        int y = offset.y + pieceCoords[i].y;
        rect.setPosition(x * blockSize, y * blockSize);
        window.draw(rect);
    }
}

void SFMLRenderer::render(const gameBoard& board,
                          const Tetromino& activePiece,
                          const Tetromino& nextPiece,
                          const Score& score) {
    window.clear(sf::Color::Black);
    drawBoard(board);
    // active piece is positioned relative to board pivot
    drawPiece(activePiece, sf::Vector2i(board.getPivot().x, board.getPivot().y));

    // Draw next piece preview on the right side
    int previewOffsetX = boardWidth * blockSize + 50;
    int previewOffsetY = 50;
    const coords* nextCoords = nextPiece.getCoords();
    // Normalise next piece to origin (0,0) for preview
    int minX = nextCoords[0].x, minY = nextCoords[0].y;
    for (int i = 1; i < 4; ++i) {
        minX = std::min(minX, nextCoords[i].x);
        minY = std::min(minY, nextCoords[i].y);
    }
    for (int i = 0; i < 4; ++i) {
        sf::RectangleShape rect(sf::Vector2f(blockSize - 1, blockSize - 1));
        rect.setFillColor(blockColor);
        int x = previewOffsetX / blockSize + (nextCoords[i].x - minX);
        int y = previewOffsetY / blockSize + (nextCoords[i].y - minY);
        rect.setPosition(x * blockSize, y * blockSize);
        window.draw(rect);
    }

    // Score display
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setString(
        "Score: " + std::to_string(score.getScore()) + "\n" +
        "Lines: " + std::to_string(score.getLines()) + "\n" +
        "Level: " + std::to_string(score.getLevel()));
    scoreText.setPosition(previewOffsetX, previewOffsetY + 200);
    window.draw(scoreText);

    window.display();
}

void SFMLRenderer::renderGameOver(const Score& score) {
    window.clear(sf::Color::Black);
    sf::Text goText;
    goText.setFont(font);
    goText.setCharacterSize(40);
    goText.setFillColor(sf::Color::Red);
    goText.setString("GAME OVER");
    goText.setPosition(100, 100);
    window.draw(goText);

    sf::Text stats;
    stats.setFont(font);
    stats.setCharacterSize(20);
    stats.setFillColor(sf::Color::White);
    stats.setString(
        "Score: " + std::to_string(score.getScore()) + "\n" +
        "Lines: " + std::to_string(score.getLines()) + "\n" +
        "Level: " + std::to_string(score.getLevel()));
    stats.setPosition(100, 200);
    window.draw(stats);

    window.display();
}

void SFMLRenderer::renderControls() {
    // Simple start screen with instructions
    renderMenu();
}

void SFMLRenderer::renderMenu() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space) {
                    return; // start the game
                }
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                    return;
                }
            }
        }
        window.clear(sf::Color::Black);
        sf::Text title;
        title.setFont(font);
        title.setCharacterSize(50);
        title.setFillColor(sf::Color::Cyan);
        title.setString("TETRIS");
        title.setPosition(100, 100);
        window.draw(title);

        sf::Text prompt;
        prompt.setFont(font);
        prompt.setCharacterSize(20);
        prompt.setFillColor(sf::Color::White);
        prompt.setString("Press Enter or Space to Start\nPress Esc to Quit");
        prompt.setPosition(100, 300);
        window.draw(prompt);

        window.display();
    }
}
