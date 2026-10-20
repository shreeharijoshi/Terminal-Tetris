#include"tetromino.hpp"
#include"gameBoard.hpp"

L_tetromino::L_tetromino(){
    pos[0] = coords(0,-1);
    pos[1] = coords(-2,0);
    pos[2] = coords(-1,0);
    pos[3] = coords(0,0);
    drop_speed = 0;
    rotation = nil;
}

void L_tetromino::rotate(gameBoard& board){
    // Determine the next rotation state in clockwise order
    Rotation nextRotation = Rotation::nil;
    switch (rotation) {
        case Rotation::nil:    nextRotation = Rotation::right; break;
        case Rotation::right:  nextRotation = Rotation::bottom; break;
        case Rotation::bottom: nextRotation = Rotation::left; break;
        case Rotation::left:   nextRotation = Rotation::nil; break;
    }

    // Compute candidate positions for each rotation state
    coords candidatePos[4];
    switch (nextRotation) {
        case Rotation::nil: // original orientation
            candidatePos[0] = coords(1,0);
            candidatePos[1] = coords(0,-2);
            candidatePos[2] = coords(0,-1);
            candidatePos[3] = coords(0,0);
            break;
        case Rotation::right:
            candidatePos[0] = coords(0,1);
            candidatePos[1] = coords(2,0);
            candidatePos[2] = coords(1,0);
            candidatePos[3] = coords(0,0);
            break;
        case Rotation::bottom:
            candidatePos[0] = coords(-1,0);
            candidatePos[1] = coords(0,2);
            candidatePos[2] = coords(0,1);
            candidatePos[3] = coords(0,0);
            break;
        case Rotation::left:
            candidatePos[0] = coords(0,-1);
            candidatePos[1] = coords(-2,0);
            candidatePos[2] = coords(-1,0);
            candidatePos[3] = coords(0,0);
            break;
    }

    // Attempt rotation; update internal state only if successful
    if (tryRotate(board, candidatePos, nextRotation)) {
        rotation = nextRotation;
    }
}

