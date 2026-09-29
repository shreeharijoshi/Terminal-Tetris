// File implementing the gameBoard class

#include<vector>
#include"gameBoard.hpp"
#include<random>
using namespace std;

gameBoard::gameBoard(){
    length = 20;
    breadth = 10;
    // used_spaces = {{}};
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

void gameBoard::hardDrop(Tetromino *t){}

bool gameBoard::canPlace(coords (&c)[4]){
    for(auto c1 : used_spaces){
        for(auto c2 : c){
            if (c1 == c2){
                return false;
            }
        }
    }
    return true;
}