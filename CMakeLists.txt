cmake_minimum_required(VERSION 3.20)

project(TerminalTetris LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Tetris
    main.cpp
    game.cpp
    gameBoard.cpp
    inputHandler.cpp
    renderer.cpp
    score.cpp
    tetromino.cpp
    i_tetromino.cpp
    j_tetromino.cpp
    l_tetromino.cpp
    o_tetromino.cpp
    s_tetromino.cpp
    t_tetromino.cpp
    z_tetromino.cpp
    tetrominoFactory.cpp
)