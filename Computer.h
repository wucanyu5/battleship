#ifndef COMPUTER_H
#define COMPUTER_H

#include <vector>
#include <utility>

/*
   Computer class:
   - Places ships randomly
   - Generates AI moves
   - Supports 3 difficulty levels
*/

class Computer {
private:
    int size;
    int difficulty; // 1 = Easy, 2 = Medium, 3 = Hard

    // Ship board (0 empty, 1 ship)
    std::vector<std::vector<int>> shipBoard;

    // Attack memory (0 unknown, 1 hit, -1 miss)
    std::vector<std::vector<int>> attackBoard;

    std::vector<int> shipLengths;

    // Medium mode
    std::vector<std::pair<int,int>> targets;

    // Hard mode
    std::vector<std::pair<int,int>> hitStack;
    bool directionLocked;
    int dirRow;
    int dirCol;

    bool canPlace(int row, int col, int length, bool horizontal);
    void placeShip(int length);

    std::pair<int,int> randomMove();
    std::pair<int,int> mediumMove();
    std::pair<int,int> hardMove();

public:
    Computer(int boardSize, int diff);

    void placeAllShips();
    const std::vector<std::vector<int>>& getShipBoard() const;

    std::pair<int,int> makeMove();
    void markResult(int row, int col, bool hit);
};

#endif