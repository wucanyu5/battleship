#include "computer.h"
#include <cstdlib>

using namespace std;

/* ================= Constructor ================= */

Computer::Computer(int boardSize, int diff) {

    size = boardSize;
    difficulty = diff;

    shipBoard.resize(size, vector<int>(size, 0));
    attackBoard.resize(size, vector<int>(size, 0));

    shipLengths = {4,3,3,2,2,2,1,1,1,1};

    directionLocked = false;
    dirRow = 0;
    dirCol = 0;
}

/* ================= Ship Placement ================= */

bool Computer::canPlace(int row, int col, int length, bool horizontal) {

    for(int i = 0; i < length; i++) {

        int r = horizontal ? row : row + i;
        int c = horizontal ? col + i : col;

        if(r >= size || c >= size)
            return false;

        if(shipBoard[r][c] != 0)
            return false;
    }

    return true;
}

void Computer::placeShip(int length) {

    while(true) {

        int row = rand() % size;
        int col = rand() % size;
        bool horizontal = rand() % 2;

        if(canPlace(row, col, length, horizontal)) {

            for(int i = 0; i < length; i++) {
                int r = horizontal ? row : row + i;
                int c = horizontal ? col + i : col;
                shipBoard[r][c] = 1;
            }

            break;
        }
    }
}

void Computer::placeAllShips() {

    for(int length : shipLengths)
        placeShip(length);
}

/* ================= Receive Shot ================= */

bool Computer::receiveShot(int row, int col) {

    if(shipBoard[row][col] == 1) {
        shipBoard[row][col] = 2;   // 2 = destroyed
        return true;
    }

    return false;
}

/* ================= Check Win ================= */

bool Computer::allShipsDestroyed() const {

    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            if(shipBoard[i][j] == 1)
                return false;

    return true;
}

/* ================= AI Core ================= */

pair<int,int> Computer::makeMove() {

    if(difficulty == 1)
        return randomMove();
    else if(difficulty == 2)
        return mediumMove();
    else
        return hardMove();
}

/* -------- Easy Mode -------- */

pair<int,int> Computer::randomMove() {

    int r, c;

    do {
        r = rand() % size;
        c = rand() % size;
    } while(attackBoard[r][c] != 0);

    return {r, c};
}

/* -------- Medium Mode -------- */

pair<int,int> Computer::mediumMove() {

    if(!targets.empty()) {
        auto move = targets.back();
        targets.pop_back();
        return move;
    }

    return randomMove();
}

/* -------- Hard Mode -------- */

pair<int,int> Computer::hardMove() {

    // Continue locked direction
    if(directionLocked && !hitStack.empty()) {

        int lastRow = hitStack.back().first;
        int lastCol = hitStack.back().second;

        int nextRow = lastRow + dirRow;
        int nextCol = lastCol + dirCol;

        if(nextRow >= 0 && nextRow < size &&
           nextCol >= 0 && nextCol < size &&
           attackBoard[nextRow][nextCol] == 0) {

            return {nextRow, nextCol};
        }
        else {
            directionLocked = false;
            hitStack.clear();
        }
    }

    return randomMove();
}

/* ================= AI Feedback ================= */

void Computer::markResult(int row, int col, bool hit) {

    attackBoard[row][col] = hit ? 1 : -1;

    /* -------- Medium AI Behavior -------- */

    if(difficulty == 2 && hit) {

        vector<pair<int,int>> neighbors = {
            {row-1,col},{row+1,col},
            {row,col-1},{row,col+1}
        };

        for(auto &p : neighbors) {

            int r = p.first;
            int c = p.second;

            if(r>=0 && r<size &&
               c>=0 && c<size &&
               attackBoard[r][c] == 0) {

                targets.push_back({r,c});
            }
        }
    }

    /* -------- Hard AI Behavior -------- */

    if(difficulty == 3 && hit) {

        hitStack.push_back({row,col});

        if(hitStack.size() >= 2) {

            int r1 = hitStack[hitStack.size()-2].first;
            int c1 = hitStack[hitStack.size()-2].second;

            dirRow = row - r1;
            dirCol = col - c1;

            directionLocked = true;
        }
    }
}
