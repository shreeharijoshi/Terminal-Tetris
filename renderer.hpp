#pragma once

class gameBoard;
class Tetromino;
class Score;

class Renderer{
public:
    void render(const gameBoard& board,
                const Tetromino& activePiece,
                const Tetromino& nextPiece,
                const Score& score);

    void renderGameOver(const Score& score);

    void renderControls();
};