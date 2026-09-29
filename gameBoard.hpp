// Header file for game board class

#pragma once
#include<vector>
#include"tetromino.hpp"
using namespace std;

class gameBoard{
    private:
    int length;
    int breadth;

    public:
    vector<coords> used_spaces;
    gameBoard();
    Tetromino* spawn();
    void softDrop(Tetromino *);
    void hardDrop(Tetromino *);
    bool canPlace(coords (&c)[4]);
};
