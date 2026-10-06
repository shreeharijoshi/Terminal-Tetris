#include"tetromino.hpp"

L_tetromino::L_tetromino(){
    pos[0] = coords(2,0);
    pos[1] = coords(0,1);
    pos[2] = coords(1,1);
    pos[3] = coords(2,1);
    origin = coords(3,0);
    drop_speed = 0;
    rotation = nil;
}

void L_tetromino::rotate(gameBoard g){
    if(rotation == nil){
        pos[0] = coords(1,0);
        pos[1] = coords(1,1);
        pos[2] = coords(1,2);
        pos[3] = coords(2,2);
        rotation = Rotation::right;
    }
    else if(rotation == Rotation::right){
        pos[0] = coords(1,0);
        pos[1] = coords(2,0);
        pos[2] = coords(3,0);
        pos[3] = coords(1,1);
        rotation = Rotation::bottom;
    }
    else if(rotation == Rotation::bottom){
        pos[0] = coords(1,0);
        pos[1] = coords(2,0);
        pos[2] = coords(2,1);
        pos[3] = coords(2,2);
        rotation = Rotation::left;
    }
    else{
        pos[0] = coords(2,0);
        pos[1] = coords(0,1);
        pos[2] = coords(1,1);
        pos[3] = coords(2,1);   
        rotation = Rotation::nil;
    }
}

void L_tetromino::move_left(gameBoard g){
    origin.x--;
    coords *newc = pos;
    for(int i=0; i<4; i++){
        newc[i] = pos[i] + origin;
    } 
    if(!g.canPlace(newc)){
        origin.x++;
    }
}
void L_tetromino::move_right(gameBoard g){
    origin.x++;
    coords *newc = pos;
    for(int i=0; i<4; i++){
        newc[i] = pos[i] + origin;
    } 
    if(!g.canPlace(newc)){
        origin.x--;
    }
}