cmake_minimum_required(VERSION 3.21)

project(CanopyTetris LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

# SFML 2.6.2 binaries live in external/ (gitignored, see README build notes)
set(SFML_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/SFML-2.6.2")
set(SFML_DIR "${SFML_ROOT_DIR}/lib/cmake/SFML" CACHE PATH "SFML cmake config dir")

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(Tetris
    src/main.cpp
    src/GameApp.cpp
)

target_link_libraries(Tetris PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

# Copy the SFML dlls next to the exe so it runs from the build folder
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(SFML_DLL_SUFFIX "-d")
else()
    set(SFML_DLL_SUFFIX "")
endif()

add_custom_command(TARGET Tetris POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SFML_ROOT_DIR}/bin/sfml-graphics-2${SFML_DLL_SUFFIX}.dll"
        "${SFML_ROOT_DIR}/bin/sfml-window-2${SFML_DLL_SUFFIX}.dll"
        "${SFML_ROOT_DIR}/bin/sfml-system-2${SFML_DLL_SUFFIX}.dll"
        "${SFML_ROOT_DIR}/bin/openal32.dll"
        "$<TARGET_FILE_DIR:Tetris>"
)
