#include "game.hpp"
#include <cmath>
#include <chrono>

Game::Game()
    : board(), activePiece(), nextPiece(), factory(),
      quitRequested(false), gameOver(false),
      gravityAccumulator(0.0), gravityInterval(1.0){
    initializePieces();
    gameOver = !initializeSpawnPosition();
}

void Game::initializePieces(){
    activePiece = factory.createRandom();
    nextPiece = factory.createRandom();
}

bool Game::initializeSpawnPosition(){
    board.setPivot(coords(4,1));

    coords activeBlocks[4];
    const coords *localOffsets = activePiece->getCoords();

    for (int i = 0; i < 4; ++i) {
        activeBlocks[i] = board.toBoardCoordinate(localOffsets[i]);
    }

    return board.canPlace(activeBlocks);
}

void Game::promoteNextPiece(){
    activePiece = std::move(nextPiece);
    nextPiece = factory.createRandom();
    gameOver = !initializeSpawnPosition();
}

void Game::finishCurrentPiece(){
    board.hardDrop(activePiece.get());
    int cleared = board.clearFullRows();
    score.addLines(cleared);
    promoteNextPiece();
}

// ---------------------------------------------------------------------------
// restart
// Resets the game state and starts a completely new game.
// ---------------------------------------------------------------------------
void Game::restart(){
    // Reset the board
    board = gameBoard();

    // Reset the score
    score = Score();

    // Reset game state
    quitRequested = false;
    gameOver = false;

    // Reset gravity
    gravityAccumulator = 0.0;
    gravityInterval = 1.0;

    // Create new pieces
    initializePieces();

    // Place the new active piece at the starting position
    gameOver = !initializeSpawnPosition();
}

void Game::handleAction(GameAction action){
    if (action == GameAction::Quit) {
        quitRequested = true;
        return;
    }

    // Restart is allowed when the game is over
    if (action == GameAction::Restart) {
        if (gameOver) {
            restart();
        }

        return;
    }

    // Ignore gameplay controls while game is over
    if (gameOver) {
        return;
    }

    switch (action){
        case GameAction::MoveLeft:
            board.moveLeft(activePiece.get());
            break;

        case GameAction::MoveRight:
            board.moveRight(activePiece.get());
            break;

        case GameAction::SoftDrop:
            board.softDrop(activePiece.get());
            break;

        case GameAction::Rotate:
            activePiece->rotate(board);
            break;

        case GameAction::HardDrop:
            finishCurrentPiece();
            break;

        case GameAction::Quit:
            break;

        case GameAction::Restart:
            break;

        case GameAction::None:
            break;
    }
}

void Game::updateGravity(double deltaTime){
    if (gameOver || deltaTime < 0.0 || !std::isfinite(deltaTime)) {
        return;
    }

    gravityAccumulator += deltaTime;

    while (gravityAccumulator >= gravityInterval) {
        if (board.softDrop(activePiece.get())) {
            gravityAccumulator -= gravityInterval;
        }
        else {
            finishCurrentPiece();
            gravityAccumulator = 0.0;
            break;
        }
    }
}

bool Game::isGameOver() const{
    return gameOver;
}

void Game::run(){
    InputHandler input;
    input.initialize();
    renderer.renderControls();

    std::chrono::steady_clock::time_point previous =
        std::chrono::steady_clock::now();

    bool gameOverDisplayed = false;

    while (!quitRequested) {
        GameAction action = input.pollAction();
        handleAction(action);

        std::chrono::steady_clock::time_point current =
            std::chrono::steady_clock::now();

        std::chrono::duration<double> elapsed = current - previous;
        previous = current;

        updateGravity(elapsed.count());

        if (gameOver) {
            if (!gameOverDisplayed) {
                renderer.renderGameOver(score);
                gameOverDisplayed = true;
            }
        }
        else {
            // A restart has happened, so allow the game-over
            // screen to be displayed again in the future.
            gameOverDisplayed = false;

            renderer.render(board, *activePiece, *nextPiece, score);
        }
    }

    input.shutdown();
}