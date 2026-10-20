#pragma once

class gameBoard;
class Tetromino;
class Score;

class Renderer {
public:
    virtual ~Renderer() = default;
    virtual void render(const gameBoard& board,
                const Tetromino& activePiece,
                const Tetromino& nextPiece,
                const Score& score);
    virtual void renderGameOver(const Score& score);
    virtual void renderControls();
};