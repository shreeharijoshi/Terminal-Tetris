#pragma once

#include <memory>
#include <random>
#include "tetromino.hpp"

class TetrominoFactory{
private:
    std::mt19937 generator;
    std::uniform_int_distribution<int> distribution;

public:
    TetrominoFactory();
    std::unique_ptr<Tetromino> createRandom();
};
