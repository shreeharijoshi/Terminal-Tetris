#include "tetrominoFactory.hpp"
#include <stdexcept>

TetrominoFactory::TetrominoFactory()
    : generator(std::random_device{}()), distribution(1, 7){
}

std::unique_ptr<Tetromino> TetrominoFactory::createRandom(){
    switch (distribution(generator)){
        case 1:
            return std::unique_ptr<Tetromino>(new I_tetromino);
        case 2:
            return std::unique_ptr<Tetromino>(new J_tetromino);
        case 3:
            return std::unique_ptr<Tetromino>(new L_tetromino);
        case 4:
            return std::unique_ptr<Tetromino>(new O_tetromino);
        case 5:
            return std::unique_ptr<Tetromino>(new S_tetromino);
        case 6:
            return std::unique_ptr<Tetromino>(new T_tetromino);
        case 7:
            return std::unique_ptr<Tetromino>(new Z_tetromino);
    }

    throw std::logic_error("TetrominoFactory generated an invalid piece type");
}
