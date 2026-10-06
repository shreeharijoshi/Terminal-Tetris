#include"tetromino.hpp"
#include"gameBoard.hpp"

O_tetromino::O_tetromino(){
    pos[0] = coords(0,0);
    pos[1] = coords(1,0);
    pos[2] = coords(0,1);
    pos[3] = coords(1,1);
    drop_speed = 0;
    rotation = nil;
}

void O_tetromino::rotate(gameBoard& board){
    const coords candidatePos[4] = {
        coords(0,0), coords(1,0), coords(0,1), coords(1,1)
    };
    tryRotate(board, candidatePos, rotation);
}
