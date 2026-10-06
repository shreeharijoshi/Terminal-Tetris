#include"tetromino.hpp"

S_tetromino::S_tetromino(){
    pos[0] = coords(1,0);
    pos[1] = coords(2,0);
    pos[2] = coords(0,1);
    pos[3] = coords(1,1);
    origin = coords(3,0);
    drop_speed = 0;
    rotation = nil;
}

void S_tetromino::rotate(gameBoard g){
    if(rotation == nil){
        pos[0] = coords(1,0);
        pos[1] = coords(1,1);
        pos[2] = coords(2,1);
        pos[3] = coords(2,2);
        rotation = Rotation::right;
    }
    else{
        pos[0] = coords(1,0);
        pos[1] = coords(2,0);
        pos[2] = coords(0,1);
        pos[3] = coords(1,1);
        rotation = Rotation::nil;
    }
}

void S_tetromino::move_left(gameBoard g){
    origin.x--;
    coords *newc = pos;
    for(int i=0; i<4; i++){
        newc[i] = pos[i] + origin;
    } 
    if(!g.canPlace(newc)){
        origin.x++;
    }
}
void S_tetromino::move_right(gameBoard g){
    origin.x++;
    coords *newc = pos;
    for(int i=0; i<4; i++){
        newc[i] = pos[i] + origin;
    } 
    if(!g.canPlace(newc)){
        origin.x--;
    }
}