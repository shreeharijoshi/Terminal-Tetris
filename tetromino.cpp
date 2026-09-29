// File implementing the tetromino classes

#include<iostream>
#include "tetromino.hpp"
#include "gameBoard.hpp"
using namespace std;

I_tetromino::I_tetromino(){
    pos[0] = coords(0,0);
    pos[1] = coords(0,1);
    pos[2] = coords(0,2);
    pos[3] = coords(0,3);
    drop_speed = 0;
    rotation = nil;
}

J_tetromino::J_tetromino(){
    pos[0] = coords(0,2);
    pos[1] = coords(1,1);
    pos[2] = coords(2,1);
    pos[3] = coords(2,2);
    drop_speed = 0;
    rotation = nil;
}

L_tetromino::L_tetromino(){
    pos[0] = coords(0,1);
    pos[1] = coords(1,1);
    pos[2] = coords(2,1);
    pos[3] = coords(2,1);
    drop_speed = 0;
    rotation = nil;
}

O_tetromino::O_tetromino(){
    pos[0] = coords(0,1);
    pos[1] = coords(0,2);
    pos[2] = coords(1,1);
    pos[3] = coords(1,2);
    drop_speed = 0;
    rotation = nil;
}

S_tetromino::S_tetromino(){
    pos[0] = coords(0,1);
    pos[1] = coords(0,2);
    pos[2] = coords(1,0);
    pos[3] = coords(1,1);
    drop_speed = 0;
    rotation = nil;
}

T_tetromino::T_tetromino(){
    pos[0] = coords(0,0);
    pos[1] = coords(0,1);
    pos[2] = coords(0,2);
    pos[3] = coords(1,1);
    drop_speed = 0;
    rotation = nil;
}

Z_tetromino::Z_tetromino(){
    pos[0] = coords(0,1);
    pos[1] = coords(0,2);
    pos[2] = coords(1,2);
    pos[3] = coords(1,3);
    drop_speed = 0;
    rotation = nil;
}