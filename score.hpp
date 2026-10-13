#pragma once

class Score{
private:
    int score;
    int lines;
    int level;

public:
    Score();

    void addLines(int cleared);

    int getScore() const;
    int getLines() const;
    int getLevel() const;
};
