#include "Shooting.h"
#include <iostream>
#include <cctype>

using namespace std;

bool Shooting::parseInput(int& row, int& col) {

    string input;
    cout << "Enter coordinate (A0 - J9): ";
    cin >> input;

    if(input.size() != 2)
        return false;

    char r = toupper(input[0]);
    char c = input[1];

    if(r < 'A' || r > 'J')
        return false;

    if(!isdigit(c))
        return false;

    row = r - 'A';
    col = c - '0';

    return true;
}

void Shooting::playerTurn(Player& player, Computer& cpu) {

    int row, col;

    while(!parseInput(row, col))
        cout << "Invalid input.\n";

    bool hit = cpu.receiveShot(row, col);

    if(hit)
        cout << "Player HIT!\n";
    else
        cout << "Player MISS!\n";
}

void Shooting::computerTurn(Player& player, Computer& cpu) {

    auto move = cpu.makeMove();

    int row = move.first;
    int col = move.second;

    bool hit = player.receiveShot(row, col);

    cout << "Computer shoots: "
         << char('A' + row) << col << endl;

    if(hit)
        cout << "Computer HIT!\n";
    else
        cout << "Computer MISS!\n";

    cpu.markResult(row, col, hit);
}

void Shooting::drawBoards(const Player& player, const Computer& cpu) {

    cout << "\n--- PLAYER BOARD ---\n";
    player.drawBoard(true);

    cout << "\n--- COMPUTER BOARD ---\n";

    const auto& board = cpu.getShipBoard();

    cout << "   0 1 2 3 4 5 6 7 8 9\n";

    for(int i = 0; i < SIZE; i++) {
        cout << char('A'+i) << "  ";
        for(int j = 0; j < SIZE; j++) {

            if(board[i][j] == 2)
                cout << "X ";
            else
                cout << ". ";
        }
        cout << endl;
    }
}