#pragma once

#include <memory>
#include "gameBoard.hpp"
#include "inputHandler.hpp"
#include "renderer.hpp"
#include "score.hpp"
#include "tetrominoFactory.hpp"

class Game{
private:
    gameBoard board;
    std::unique_ptr<Tetromino> activePiece;
    std::unique_ptr<Tetromino> nextPiece;
    TetrominoFactory factory;
    Score score;
    Renderer renderer;
    bool quitRequested;
    bool gameOver;
    double gravityAccumulator;
    double gravityInterval;

    void initializePieces();
    bool initializeSpawnPosition();
    void promoteNextPiece();
    void finishCurrentPiece();

public:
    Game();
    void handleAction(GameAction action);
    void updateGravity(double deltaTime);
    bool isGameOver() const;
    void run();
};
