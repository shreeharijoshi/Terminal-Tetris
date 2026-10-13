#include "tetromino.hpp"
#include "gameBoard.hpp"
#include"gameBoard.hpp"

I_tetromino::I_tetromino(){
    pos[0] = coords(-1,0);
    pos[1] = coords(0,0);
    pos[2] = coords(1,0);
    pos[3] = coords(2,0);
    drop_speed = 0;
    rotation = nil;
}

void I_tetromino::rotate(gameBoard& board){
    coords candidatePos[4];
    Rotation candidateRotation;
    if(rotation == nil){
        candidatePos[0] = coords(0,-1);
        candidatePos[1] = coords(0,0);
        candidatePos[2] = coords(0,1);
        candidatePos[3] = coords(0,2);
        candidateRotation = Rotation::right;
    }
    else if(rotation == Rotation::right){
        candidatePos[0] = coords(1,0);
        candidatePos[1] = coords(0,0);
        candidatePos[2] = coords(-1,0);
        candidatePos[3] = coords(-2,0);
        candidateRotation = Rotation::bottom;
    }
    else if(rotation == Rotation::bottom){
        candidatePos[0] = coords(0,1);
        candidatePos[1] = coords(0,0);
        candidatePos[2] = coords(0,-1);
        candidatePos[3] = coords(0,-2);
        candidateRotation = Rotation::left;
    }
    else{
        candidatePos[0] = coords(-1,0);
        candidatePos[1] = coords(0,0);
        candidatePos[2] = coords(1,0);
        candidatePos[3] = coords(2,0);
        candidateRotation = Rotation::nil;
    }
    tryRotate(board, candidatePos, candidateRotation);
}
