// File implementing the gameBoard class

#include<vector>
#include"gameBoard.hpp"
#include<random>
using namespace std;

gameBoard::gameBoard(){
    length = 20;
    breadth = 10;
}

Tetromino* gameBoard::spawn(){
    Tetromino *t;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1,7);
    switch(dist(gen)){
        case 1: 
            t = new I_tetromino;
            break;
        case 2:
            t = new J_tetromino;
            break;
        case 3:
            t = new L_tetromino;
            break;
        case 4:
            t = new O_tetromino;
            break;
        case 5:
            t = new S_tetromino;
            break;
        case 6:
            t = new T_tetromino;
            break;
        case 7:
            t = new Z_tetromino;
            break;
    }
    return t;
}

void gameBoard::softDrop(Tetromino *t){}

void gameBoard::hardDrop(Tetromino *t){
    coords * currentPos = t->getCoords();
    while(canPlace(currentPos)){
        for(int i=0; i<4; i++){
            currentPos[i].y++;
        }
    }
    for(int i=0; i<4; i++){
        used_spaces.push_back(currentPos[i]);
    }
}

bool gameBoard::canPlace(coords *c){
    for(auto c1 : used_spaces){
        for(int i=0; i<4; i++){
            if (c1 == *(c+i)){
                return false;
            }
        }
    }
    for(int i=0; i<4; i++){
        if (c[i].x < 0 || c[i].y < 0 || c[i].x >= 10 || c[i].y >= 20){
            return false;
        }
    }
    return true;
}