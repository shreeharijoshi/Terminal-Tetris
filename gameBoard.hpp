// Header file for game board class

#pragma once
#include<vector>
#include"tetromino.hpp"
using namespace std;

class gameBoard{
    private:
    int length;
    int breadth;
    coords pivot;

    public:
    vector<coords> used_spaces;
    gameBoard();
    int getLength() const;
    int getBreadth() const;
    coords getPivot() const;
    void setPivot(const coords& position);
    coords toBoardCoordinate(const coords& localOffset) const;
    void moveLeft(Tetromino *);
    void moveRight(Tetromino *);
    bool softDrop(Tetromino *);
    void hardDrop(Tetromino *);
    int clearFullRows();
    bool canPlace(const coords *) const;
};
