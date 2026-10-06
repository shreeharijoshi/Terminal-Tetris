#include"tetromino.hpp"

O_tetromino::O_tetromino(){
    pos[0] = coords(1,0);
    pos[1] = coords(2,0);
    pos[2] = coords(1,1);
    pos[3] = coords(2,1);
    origin = coords(3,0);
    drop_speed = 0;
    rotation = nil;
}

void O_tetromino::move_left(gameBoard g){
    origin.x--;
    coords *newc = pos;
    for(int i=0; i<4; i++){
        newc[i] = pos[i] + origin;
    } 
    if(!g.canPlace(newc)){
        origin.x++;
    }
}
void O_tetromino::move_right(gameBoard g){
    origin.x++;
    coords *newc = pos;
    for(int i=0; i<4; i++){
        newc[i] = pos[i] + origin;
    } 
    if(!g.canPlace(newc)){
        origin.x--;
    }
}