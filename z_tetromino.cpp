#include"tetromino.hpp"

Z_tetromino::Z_tetromino(){
    pos[0] = coords(0,1);
    pos[1] = coords(0,2);
    pos[2] = coords(1,2);
    pos[3] = coords(1,3);
    drop_speed = 0;
    rotation = nil;
}

void Z_tetromino::rotate(gameBoard g){
    if(rotation == nil || rotation == Rotation::bottom){
        pos[0] = coords(0,2);
        pos[1] = coords(1,1);
        pos[2] = coords(1,2);
        pos[3] = coords(2,1);
        rotation = Rotation::right;
    }
    else {
        pos[0] = coords(0,1);
        pos[1] = coords(0,2);
        pos[2] = coords(1,2);
        pos[3] = coords(1,3);
        rotation = Rotation::bottom;
    }
}

void Z_tetromino::move_left(gameBoard g){
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
void Z_tetromino::move_right(gameBoard g){
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