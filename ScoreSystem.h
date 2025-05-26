#pragma once
#include <iostream>
#include <vector>
#include "card.h"

template <typename T>
class ScoreSystem {
private:
    T score;

public:
    ScoreSystem() : score(0) {}

    void addScore(const Card& card) {
        score += card.getValue();
    }

    T getScore() const {
        return score;
    }

    void resetScore() {
        score = 0;
    }

    void printScore() const {
        std::cout << "Ai gresit! - Esti in corabie de: " << score << std::endl;
    }
};

