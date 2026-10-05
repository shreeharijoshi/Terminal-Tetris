#include "tetromino.hpp"
#include"gameBoard.hpp"

I_tetromino::I_tetromino(){
    pos[0] = coords(1,0);
    pos[1] = coords(1,1);
    pos[2] = coords(1,2);
    pos[3] = coords(1,3);
    drop_speed = 0;
    rotation = nil;
}

void I_tetromino::rotate(gameBoard g){
    if(rotation == nil){
        pos[0] = coords(0,2);
        pos[1] = coords(1,2);
        pos[2] = coords(2,2);
        pos[3] = coords(3,2);
        rotation = Rotation::right;
    }
    else if(rotation == Rotation::right){
        pos[0] = coords(2,0);
        pos[1] = coords(2,1);
        pos[2] = coords(2,2);
        pos[3] = coords(2,3);
        rotation = Rotation::bottom;
    }
    else if(rotation == Rotation::bottom){
        pos[0] = coords(0,1);
        pos[1] = coords(1,1);
        pos[2] = coords(2,1);
        pos[3] = coords(3,1);
        rotation = Rotation::left;
    }
    else{
        pos[0] = coords(1,0);
        pos[1] = coords(1,1);
        pos[2] = coords(1,2);
        pos[3] = coords(1,3);
        rotation = Rotation::nil;
    }
}

void I_tetromino::move_left(gameBoard g){
    coords *newc = pos;
    for(int i=0; i<4; i++){
        newc[i].x--;
    }
    if(g.canPlace(newc)){
        for(int i=0; i<4; i++){
            pos[i] = newc[i];
        }
    }
    
}
void I_tetromino::move_right(gameBoard g){
    coords *newc = pos;
    for(int i=0; i<4; i++){
        newc[i].x++;
    }
    if(g.canPlace(newc)){
        for(int i=0; i<4; i++){
            pos[i] = newc[i];
        }
    }
}
