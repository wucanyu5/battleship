#ifndef COMPUTER_H
#define COMPUTER_H

#include <vector>
#include <utility>

class Computer {
private:
    int size;          // Board size (10)
    int difficulty;    // 1=Easy, 2=Medium, 3=Hard

    // 0 = empty
    // 1 = ship
    // 2 = destroyed
    std::vector<std::vector<int>> shipBoard;

    // AI memory
    // 0 = not attacked
    // 1 = hit
    // -1 = miss
    std::vector<std::vector<int>> attackBoard;

    std::vector<int> shipLengths;

    // Medium AI
    std::vector<std::pair<int,int>> targets;

    // Hard AI
    std::vector<std::pair<int,int>> hitStack;
    bool directionLocked;
    int dirRow;
    int dirCol;

    // Ship placement helpers
    bool canPlace(int row, int col, int length, bool horizontal);
    void placeShip(int length);

    // AI move types
    std::pair<int,int> randomMove();
    std::pair<int,int> mediumMove();
    std::pair<int,int> hardMove();

public:
    Computer(int boardSize, int diff);

    void placeAllShips();

    // When player shoots computer
    bool receiveShot(int row, int col);

    bool allShipsDestroyed() const;

    const std::vector<std::vector<int>>& getShipBoard() const;

    // AI shooting
    std::pair<int,int> makeMove();
    void markResult(int row, int col, bool hit);
};

#endif
