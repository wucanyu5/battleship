#include "Computer.h"
#include <cstdlib>

using namespace std;

/* Constructor */
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

        if(r >= size || c >= size) return false;
        if(shipBoard[r][c] != 0) return false;
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

const vector<vector<int>>& Computer::getShipBoard() const {
    return shipBoard;
}

/* ================= AI ================= */

pair<int,int> Computer::makeMove() {

    if(difficulty == 1)
        return randomMove();
    else if(difficulty == 2)
        return mediumMove();
    else
        return hardMove();
}

/* Easy: random shooting */
pair<int,int> Computer::randomMove() {

    int r, c;

    do {
        r = rand() % size;
        c = rand() % size;
    } while(attackBoard[r][c] != 0);

    return {r, c};
}

/* Medium: attack neighbors after hit */
pair<int,int> Computer::mediumMove() {

    if(!targets.empty()) {
        auto move = targets.back();
        targets.pop_back();
        return move;
    }

    return randomMove();
}

/* Hard: direction locking and chasing */
pair<int,int> Computer::hardMove() {

    // Continue in locked direction
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

    // One hit → try neighbors
    if(hitStack.size() == 1) {

        int row = hitStack[0].first;
        int col = hitStack[0].second;

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

                return {r,c};
            }
        }
    }

    return randomMove();
}

/* Process shot result */
void Computer::markResult(int row, int col, bool hit) {

    attackBoard[row][col] = hit ? 1 : -1;

    if(difficulty == 1) return;

    // Medium behavior
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

    // Hard behavior
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