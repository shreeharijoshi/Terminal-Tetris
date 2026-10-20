#include "tetromino.hpp"
#include "gameBoard.hpp"

I_tetromino::I_tetromino(){
    pos[0] = coords(-1,0);
    pos[1] = coords(0,0);
    pos[2] = coords(1,0);
    pos[3] = coords(2,0);
    drop_speed = 0;
    rotation = nil;
}

void I_tetromino::rotate(gameBoard& board){
    // Determine the next rotation state in clockwise order
    Rotation nextRotation = Rotation::nil;
    switch (rotation) {
        case Rotation::nil:    nextRotation = Rotation::right; break;
        case Rotation::right:  nextRotation = Rotation::bottom; break;
        case Rotation::bottom: nextRotation = Rotation::left; break;
        case Rotation::left:   nextRotation = Rotation::nil; break;
    }

    // Compute candidate positions for the I piece relative to the pivot (pos[1])
    coords candidatePos[4];
    switch (nextRotation) {
        case Rotation::nil: // vertical (original)
            candidatePos[0] = coords(-1,0);
            candidatePos[1] = coords(0,0);
            candidatePos[2] = coords(1,0);
            candidatePos[3] = coords(2,0);
            break;
        case Rotation::right: // horizontal, pivot at left block
            candidatePos[0] = coords(0,-1);
            candidatePos[1] = coords(0,0);
            candidatePos[2] = coords(0,1);
            candidatePos[3] = coords(0,2);
            break;
        case Rotation::bottom: // vertical reversed
            candidatePos[0] = coords(1,0);
            candidatePos[1] = coords(0,0);
            candidatePos[2] = coords(-1,0);
            candidatePos[3] = coords(-2,0);
            break;
        case Rotation::left: // horizontal reversed
            candidatePos[0] = coords(0,1);
            candidatePos[1] = coords(0,0);
            candidatePos[2] = coords(0,-1);
            candidatePos[3] = coords(0,-2);
            break;
    }

    // Attempt rotation; only update internal rotation if successful
    if (tryRotate(board, candidatePos, nextRotation)) {
        rotation = nextRotation;
    }
}
