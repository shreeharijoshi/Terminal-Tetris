// Header file for tetromino classes

#pragma once
using namespace std;

class gameBoard;

typedef struct coords{
    int x;
    int y;
    coords(): x(0), y(0) {}
    coords(int a, int b){
        x = a;
        y = b;
    }
    bool operator ==(const coords& c) const{
        if ((x == c.x) && (y == c.y)) return true;
        return false;
    }
    coords operator +(coords c){
        coords newc = coords(x+c.x, y+c.y);
        return newc;
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
    bool tryRotate(gameBoard& board, const coords candidatePos[4], Rotation candidateRotation);

    public:
    coords * getCoords(){
        return pos;
    }
    const coords * getCoords() const;
    virtual void rotate(gameBoard& board) = 0;
    virtual ~Tetromino();
};

class I_tetromino : public Tetromino{
    public:
    I_tetromino();
    void rotate(gameBoard& board);
};

class J_tetromino : public Tetromino{
    public:
    J_tetromino();
    void rotate(gameBoard& board);
};

class L_tetromino : public Tetromino{
    public:
    L_tetromino();
    void rotate(gameBoard& board);
};

class O_tetromino : public Tetromino{
    public:
    O_tetromino();
    void rotate(gameBoard& board);
};

class S_tetromino : public Tetromino{
    public:
    S_tetromino();
    void rotate(gameBoard& board);
};

class T_tetromino : public Tetromino{
    public:
    T_tetromino();
    void rotate(gameBoard& board);
};

class Z_tetromino : public Tetromino{
    public:
    Z_tetromino();
    void rotate(gameBoard& board);
};