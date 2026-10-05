#include"tetromino.hpp"

O_tetromino::O_tetromino(){
    pos[0] = coords(0,1);
    pos[1] = coords(0,2);
    pos[2] = coords(1,1);
    pos[3] = coords(1,2);
    drop_speed = 0;
    rotation = nil;
}

void O_tetromino::move_left(gameBoard g){
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
void O_tetromino::move_right(gameBoard g){
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