#ifndef SHOOTING_H
#define SHOOTING_H

#include "player.h"
#include "computer.h"

class Shooting {
private:
    // Parse user input like A5 into row/col
    bool parseInput(int& row, int& col);

public:
    // Draw both boards
    void drawBoards(const Player& player, const Computer& cpu);

    // Player attacks computer
    void playerTurn(Player& player, Computer& cpu);

    // Computer attacks player
    void computerTurn(Player& player, Computer& cpu);
};

#endif
