// File implementing the gameBoard class

#include<vector>
#include"gameBoard.hpp"
using namespace std;

gameBoard::gameBoard(){
    length = 20;
    breadth = 10;
    pivot = coords(0,0);
}

int gameBoard::getLength() const{
    return length;
}

int gameBoard::getBreadth() const{
    return breadth;
}

coords gameBoard::getPivot() const{
    return pivot;
}

void gameBoard::setPivot(const coords& position){
    pivot = position;
}

coords gameBoard::toBoardCoordinate(const coords& localOffset) const{
    return coords(pivot.x + localOffset.x, pivot.y + localOffset.y);
}

void gameBoard::moveLeft(Tetromino *t){
    if (t == nullptr) {
        return;
    }

    coords candidatePivot = pivot;
    --candidatePivot.x;
    coords candidateBlocks[4];
    const coords *localOffsets = t->getCoords();
    for (int i = 0; i < 4; ++i) {
        candidateBlocks[i] = coords(
            candidatePivot.x + localOffsets[i].x,
            candidatePivot.y + localOffsets[i].y
        );
    }

    if (canPlace(candidateBlocks)) {
        pivot = candidatePivot;
    }
}

void gameBoard::moveRight(Tetromino *t){
    if (t == nullptr) {
        return;
    }

    coords candidatePivot = pivot;
    ++candidatePivot.x;
    coords candidateBlocks[4];
    const coords *localOffsets = t->getCoords();
    for (int i = 0; i < 4; ++i) {
        candidateBlocks[i] = coords(
            candidatePivot.x + localOffsets[i].x,
            candidatePivot.y + localOffsets[i].y
        );
    }

    if (canPlace(candidateBlocks)) {
        pivot = candidatePivot;
    }
}

bool gameBoard::softDrop(Tetromino *t){
    if (t == nullptr) {
        return false;
    }

    coords candidatePivot = pivot;
    ++candidatePivot.y;
    coords candidateBlocks[4];
    const coords *localOffsets = t->getCoords();
    for (int i = 0; i < 4; ++i) {
        candidateBlocks[i] = coords(
            candidatePivot.x + localOffsets[i].x,
            candidatePivot.y + localOffsets[i].y
        );
    }

    if (canPlace(candidateBlocks)) {
        pivot = candidatePivot;
        return true;
    }

    return false;
}

void gameBoard::hardDrop(Tetromino *t){
    if (t == nullptr) {
        return;
    }

    const coords *localOffsets = t->getCoords();
    coords currentPivot = pivot;

    coords currentBlocks[4];
    for (int i = 0; i < 4; ++i) {
        currentBlocks[i] = coords(
            currentPivot.x + localOffsets[i].x,
            currentPivot.y + localOffsets[i].y
        );
    }

    if (!canPlace(currentBlocks)) {
        return;
    }

    while (true) {
        coords candidatePivot = currentPivot;
        ++candidatePivot.y;

        coords candidateBlocks[4];
        for (int i = 0; i < 4; ++i) {
            candidateBlocks[i] = coords(
                candidatePivot.x + localOffsets[i].x,
                candidatePivot.y + localOffsets[i].y
            );
        }

        if (!canPlace(candidateBlocks)) {
            break;
        }

        currentPivot = candidatePivot;
    }

    pivot = currentPivot;

    for (int i = 0; i < 4; ++i) {
        used_spaces.push_back(toBoardCoordinate(localOffsets[i]));
    }
}

int gameBoard::clearFullRows(){
    vector<bool> fullRows(length, true);
    for (int row = 0; row < length; ++row) {
        for (int x = 0; x < breadth; ++x) {
            bool occupied = false;
            for (const coords& occupiedCell : used_spaces) {
                if (occupiedCell.x == x && occupiedCell.y == row) {
                    occupied = true;
                    break;
                }
            }
            if (!occupied) {
                fullRows[row] = false;
                break;
            }
        }
    }

    int clearedRows = 0;
    for (bool full : fullRows) {
        if (full) {
            ++clearedRows;
        }
    }

    if (clearedRows == 0) {
        return 0;
    }

    vector<coords> remaining;
    for (const coords& cell : used_spaces) {
        if (cell.y < 0 || cell.y >= length) {
            remaining.push_back(cell);
            continue;
        }

        if (fullRows[cell.y]) {
            continue;
        }

        int rowsBelow = 0;
        for (int row = cell.y + 1; row < length; ++row) {
            if (fullRows[row]) {
                ++rowsBelow;
            }
        }
        remaining.push_back(coords(cell.x, cell.y + rowsBelow));
    }

    used_spaces = remaining;
    return clearedRows;
}

bool gameBoard::canPlace(const coords *c) const{
    for (const coords& used : used_spaces) {
        for (int i = 0; i < 4; ++i) {
            if (used == c[i]) {
                return false;
            }
        }
    }

    for (int i = 0; i < 4; ++i) {
        if (c[i].x < 0 || c[i].y < 0 || c[i].x >= breadth || c[i].y >= length){
            return false;
        }
    }
    return true;
}