#define NOMINMAX
#include <windows.h>

#include "renderer.hpp"
#include "gameBoard.hpp"
#include "tetromino.hpp"
#include "score.hpp"

#include <iostream>
#include <algorithm>

static void enableANSI()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hOut == INVALID_HANDLE_VALUE)
        return;

    DWORD mode = 0;

    if (!GetConsoleMode(hOut, &mode))
        return;

    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    SetConsoleMode(hOut, mode);

    // Hide terminal cursor to reduce visual distraction/flicker
    std::cout << "\033[?25l";
}

static bool isLockedCell(const gameBoard& board, int x, int y)
{
    for (const coords& cell : board.used_spaces)
    {
        if (cell.x == x && cell.y == y)
            return true;
    }

    return false;
}

static bool isActiveCell(const gameBoard& board,
                         const Tetromino& piece,
                         int x,
                         int y)
{
    coords pivot = board.getPivot();
    const coords* pieceCoords = piece.getCoords();

    for (int i = 0; i < 4; i++)
    {
        int absoluteX = pivot.x + pieceCoords[i].x;
        int absoluteY = pivot.y + pieceCoords[i].y;

        if (absoluteX == x && absoluteY == y)
            return true;
    }

    return false;
}

void Renderer::render(const gameBoard& board,
                      const Tetromino& activePiece,
                      const Tetromino& nextPiece,
                      const Score& score)
{
    enableANSI();

    // Move cursor to top-left without clearing the whole screen
    std::cout << "\033[H";

    int height = board.getLength();
    int width = board.getBreadth();

    std::cout << "========== TETRIS ==========\n\n";

    // Top border
    std::cout << "+";

    for (int x = 0; x < width; x++)
        std::cout << "--";

    std::cout << "+\n";

    // Game board
    for (int y = 0; y < height; y++)
    {
        std::cout << "|";

        for (int x = 0; x < width; x++)
        {
            if (isActiveCell(board, activePiece, x, y))
            {
                std::cout << "[]";
            }
            else if (isLockedCell(board, x, y))
            {
                std::cout << "##";
            }
            else
            {
                std::cout << "  ";
            }
        }

        std::cout << "|";

        // NEXT label
        if (y == 1)
            std::cout << "   NEXT";

        // Next-piece box
        if (y == 2)
            std::cout << "   +--------+";

        if (y >= 3 && y <= 6)
        {
            std::cout << "   |";

            int previewY = y - 3;

            const coords* nextCoords = nextPiece.getCoords();

            int minX = nextCoords[0].x;
            int minY = nextCoords[0].y;

            for (int i = 1; i < 4; i++)
            {
                minX = (std::min)(minX, nextCoords[i].x);
                minY = (std::min)(minY, nextCoords[i].y);
            }

            for (int previewX = 0; previewX < 4; previewX++)
            {
                bool occupied = false;

                for (int i = 0; i < 4; i++)
                {
                    int normalizedX = nextCoords[i].x - minX;
                    int normalizedY = nextCoords[i].y - minY;

                    if (normalizedX == previewX &&
                        normalizedY == previewY)
                    {
                        occupied = true;
                        break;
                    }
                }

                if (occupied)
                    std::cout << "[]";
                else
                    std::cout << "  ";
            }

            std::cout << "|";
        }

        // Score information
        if (y == 8)
            std::cout << "   SCORE: " << score.getScore();

        if (y == 9)
            std::cout << "   LINES: " << score.getLines();

        if (y == 10)
            std::cout << "   LEVEL: " << score.getLevel();

        std::cout << "\n";
    }

    // Bottom border
    std::cout << "+";

    for (int x = 0; x < width; x++)
        std::cout << "--";

    std::cout << "+\n\n";

    // Controls
    std::cout << "Controls:\n";
    std::cout << "A/D or Left/Right : Move\n";
    std::cout << "S/Down             : Soft drop\n";
    std::cout << "W/Up               : Rotate\n";
    std::cout << "Space              : Hard drop\n";
    std::cout << "Q/Escape           : Quit";

    // Flush complete frame
    std::cout.flush();
}

void Renderer::renderGameOver(const Score& score)
{
    enableANSI();

    // Clear screen once when entering game-over screen
    std::cout << "\033[2J\033[H";

    std::cout << "\n";
    std::cout << "============================\n";
    std::cout << "         GAME OVER          \n";
    std::cout << "============================\n\n";

    std::cout << "Final Score : " << score.getScore() << "\n";
    std::cout << "Lines       : " << score.getLines() << "\n";
    std::cout << "Level       : " << score.getLevel() << "\n\n";

    std::cout << "Press Q or Escape to quit.\n";

    std::cout.flush();
}

void Renderer::renderControls()
{
    enableANSI();

    std::cout << "\033[2J\033[H";

    std::cout << "========== TETRIS ==========\n\n";

    std::cout << "Controls:\n";
    std::cout << "A / Left Arrow   : Move Left\n";
    std::cout << "D / Right Arrow  : Move Right\n";
    std::cout << "S / Down Arrow   : Soft Drop\n";
    std::cout << "W / Up Arrow     : Rotate\n";
    std::cout << "Space            : Hard Drop\n";
    std::cout << "Q / Escape       : Quit\n\n";

    std::cout << "Starting game...\n";

    std::cout.flush();
}