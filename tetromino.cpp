#include "tetromino.hpp"
#include "gameBoard.hpp"

Tetromino::~Tetromino() = default;

const coords * Tetromino::getCoords() const{
    return pos;
}

bool Tetromino::tryRotate(
    gameBoard& board,
    const coords candidatePos[4],
    Rotation candidateRotation
){
    coords candidateBlocks[4];
    for (int i = 0; i < 4; ++i) {
        candidateBlocks[i] = board.toBoardCoordinate(candidatePos[i]);
    }

    if (!board.canPlace(candidateBlocks)) {
        return false;
    }

    for (int i = 0; i < 4; ++i) {
        pos[i] = candidatePos[i];
    }
    rotation = candidateRotation;
    return true;
}
