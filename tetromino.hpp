// Header file for tetromino classes

#pragma once
#include"gameBoard.hpp"
using namespace std;

typedef struct coords{
    int x;
    int y;
    coords(): x(0), y(0) {}
    coords(int a, int b){
        x = a;
        y = b;
    }
    bool operator ==(coords c){
        if ((x == c.x) && (y == c.y)) return true;
        return false;
    }
    coords operator ++(){
        coords newc = coords(x, y+1);
        return newc;
    }
} coords;

enum Rotation{
    nil = 0,
    right,
    bottom,
    left
};

class Tetromino{
    protected:
    coords pos[4]; 
    int drop_speed;
    Rotation rotation;

    public:
    coords * getCoords(){
        return pos;
    }
    virtual void move_left(gameBoard g) = 0;
    virtual void move_right(gameBoard g) = 0;
    virtual void rotate(gameBoard g);
    virtual ~Tetromino();
};

class I_tetromino : public Tetromino{
    public:
    I_tetromino();
    void rotate(gameBoard g);
    void move_left(gameBoard g);
    void move_right(gameBoard g);
};

class J_tetromino : public Tetromino{
    public:
    J_tetromino();
    void rotate(gameBoard g);
    void move_left(gameBoard g);
    void move_right(gameBoard g);
};

class L_tetromino : public Tetromino{
    public:
    L_tetromino();
    void rotate(gameBoard g);
    void move_left(gameBoard g);
    void move_right(gameBoard g);
};

class O_tetromino : public Tetromino{
    public:
    O_tetromino();
    void rotate(gameBoard g);
    void move_left(gameBoard g);
    void move_right(gameBoard g);
};

class S_tetromino : public Tetromino{
    public:
    S_tetromino();
    void rotate(gameBoard g);
    void move_left(gameBoard g);
    void move_right(gameBoard g);
};

class T_tetromino : public Tetromino{
    public:
    T_tetromino();
    void rotate(gameBoard g);
    void move_left(gameBoard g);
    void move_right(gameBoard g);
};

class Z_tetromino : public Tetromino{
    public:
    Z_tetromino();
    void rotate(gameBoard g);
    void move_left(gameBoard g);
    void move_right(gameBoard g);
};