cmake_minimum_required(VERSION 3.20)

project(TerminalTetris LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Fetch SFML
# NOTE: SFML is expected to be installed on the system.
# On Windows, download the SFML SDK (https://www.sfml-dev.org/download.php) and set CMAKE_PREFIX_PATH
# to the SFML installation directory, or place the SFML libraries in a path known to CMake.
# Then the find_package call below will locate SFML.

# Find SFML libraries
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
add_executable(Tetris
    main.cpp
    game.cpp
    gameBoard.cpp
    inputHandler.cpp
    renderer.cpp
    sfml_renderer.cpp
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

target_link_libraries(Tetris sfml::Graphics sfml::Window sfml::System)