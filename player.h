#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

class Player {
private:
    static const int SIZE = 10;

    // 0 = empty
    // 1 = ship
    // 3 = hit
    // 4 = miss
    std::vector<std::vector<int>> shipBoard;

public:
    Player();

    void placeShips();   // simple random placement
    void drawBoard(bool showShips = true) const;

    bool receiveShot(int row, int col);
    bool allShipsDestroyed() const;

    const std::vector<std::vector<int>>& getBoard() const;
};

#endif
