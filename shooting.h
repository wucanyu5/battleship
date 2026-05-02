#ifndef SHOOTING_H
#define SHOOTING_H

#include "Player.h"
#include "Computer.h"

class Shooting {
public:
    void drawBoards(const Player& player, const Computer& cpu);

    void playerTurn(Player& player, Computer& cpu);

    void computerTurn(Player& player, Computer& cpu);
};

#endif