#include "score.hpp"

Score::Score()
    : score(0), lines(0), level(1){
}

void Score::addLines(int cleared){
    if (cleared <= 0 || cleared > 4) {
        return;
    }

    int points = 0;
    switch (cleared){
        case 1:
            points = 100;
            break;
        case 2:
            points = 300;
            break;
        case 3:
            points = 500;
            break;
        case 4:
            points = 800;
            break;
    }

    score += points * level;
    lines += cleared;
    level = (lines / 10) + 1;
}

int Score::getScore() const{
    return score;
}

int Score::getLines() const{
    return lines;
}

int Score::getLevel() const{
    return level;
}
