#include "Player.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Player::Player() {
    shipBoard.resize(SIZE, vector<int>(SIZE, 0));
}

/* Simple random ship placement */
void Player::placeShips() {

    vector<int> ships = {4,3,3,2,2,2,1,1,1,1};

    for(int length : ships) {

        while(true) {

            int row = rand() % SIZE;
            int col = rand() % SIZE;
            bool horizontal = rand() % 2;

            bool canPlace = true;

            for(int i = 0; i < length; i++) {
                int r = horizontal ? row : row + i;
                int c = horizontal ? col + i : col;

                if(r >= SIZE || c >= SIZE || shipBoard[r][c] != 0) {
                    canPlace = false;
                    break;
                }
            }

            if(canPlace) {
                for(int i = 0; i < length; i++) {
                    int r = horizontal ? row : row + i;
                    int c = horizontal ? col + i : col;
                    shipBoard[r][c] = 1;
                }
                break;
            }
        }
    }
}

void Player::drawBoard(bool showShips) const {

    cout << "   0 1 2 3 4 5 6 7 8 9\n";

    for(int i = 0; i < SIZE; i++) {
        cout << char('A' + i) << "  ";
        for(int j = 0; j < SIZE; j++) {

            if(shipBoard[i][j] == 0)
                cout << ". ";
            else if(shipBoard[i][j] == 1)
                cout << (showShips ? "O " : ". ");
            else if(shipBoard[i][j] == 3)
                cout << "X ";
            else if(shipBoard[i][j] == 4)
                cout << "* ";
        }
        cout << endl;
    }
}

bool Player::receiveShot(int row, int col) {

    if(shipBoard[row][col] == 1) {
        shipBoard[row][col] = 3;
        return true;
    }

    if(shipBoard[row][col] == 0)
        shipBoard[row][col] = 4;

    return false;
}

bool Player::allShipsDestroyed() const {

    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            if(shipBoard[i][j] == 1)
                return false;

    return true;
}

const vector<vector<int>>& Player::getBoard() const {
    return shipBoard;
}
