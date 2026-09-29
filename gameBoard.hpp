// Header file for game board class

#pragma once
#include<vector>
using namespace std;

class gameBoard{
    private:
    int length;
    int breadth;
    vector<vector<int>> used_spaces;

    public:
    gameBoard();
    void spawn();
    void softDrop();
    void hardDrop();
    bool canPlace(coords *);
};
