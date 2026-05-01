#include "Shooting.h"
#include <iostream>

using namespace std;

// Global score counters
int Count_Player = 0;
int Count_Computer = 0;

/*
    Constructor initializes coordinate state
*/
Shooting::Shooting() {
    Cord = "";
    x = 0;
    y = 0;
}

Shooting::~Shooting() {}

/*
    Ensures coordinates are inside valid playable range (1-10)
*/
bool Shooting::isValidCoord(int row, int col) {
    return (row >= 1 && row <= 10 && col >= 1 && col <= 10);
}

/*
    Handles player shooting input.

    Responsibilities:
    - Accept coordinate string (e.g., A5)
    - Convert ASCII input into board indices
    - Validate format and range
*/
void Shooting::Input_Coord() {

    bool correct_cord;

    do {
        cout << "   Input coordinates to shoot (Ex.: A5): ";
        cin >> Cord;

        correct_cord = false;

        if (Cord.size() == 2) {

            char letter = Cord[0];
            char number = Cord[1];

            if (letter >= 'A' && letter <= 'J' && isdigit(number)) {

                // Convert ASCII to board indices
                x = letter - 64;     // 'A' → 1
                y = number - 47;     // '0' → 1

                if (isValidCoord(x, y))
                    correct_cord = true;
            }
        }

    } while (!correct_cord);
}

/*
    Displays both boards side by side.

    Responsibilities:
    - Show full Player board (including ships)
    - Hide Computer ships except hits/misses
*/
void Shooting::Draw_Shooting() {

    cout << "                   Player                         Computer\n";
    cout << "            0 1 2 3 4 5 6 7 8 9             0 1 2 3 4 5 6 7 8 9\n";

    char letter = 'A';

    for (int i = 1; i < EIL - 1; i++) {

        // ----- PLAYER BOARD -----
        cout << "          " << letter << " ";
        for (int j = 1; j < STULP - 1; j++) {

            if (Board[i][j] == 0 || Board[i][j] == 2)
                cout << ". ";
            else if (Board[i][j] == 1)
                cout << "0 ";
            else if (Board[i][j] == 3)
                cout << "X ";
            else if (Board[i][j] == 4)
                cout << "* ";
        }

        // ----- COMPUTER BOARD -----
        cout << "          " << letter++ << " ";
        for (int j = 1; j < STULP - 1; j++) {

            if (Board1[i][j] == 3)
                cout << "X ";
            else if (Board1[i][j] == 4)
                cout << "* ";
            else
                cout << ". ";
        }

        cout << endl;
    }
}

/*
    Executes Player's attack on Computer board.

    Responsibilities:
    - Check if location already shot
    - Determine hit or miss
    - Update Computer board state
    - Update Player score
*/
void Shooting::Update_Computer_Grid() {

    while (true) {

        // Ensure position was not previously attacked
        if (Board1[x][y] != 3 && Board1[x][y] != 4) {

            if (Board1[x][y] == 1) {
                Board1[x][y] = 3;       // Mark as hit
                cout << "   Player HIT!\n";
                Count_Player++;
            }
            else {
                Board1[x][y] = 4;       // Mark as miss
                cout << "   Player MISS!\n";
            }

            break;
        }
        else {
            cout << "   Already shot here!\n";
            Input_Coord();
        }
    }
}

/*
    Executes Computer's attack on Player board.

    Responsibilities:
    1. Ask Computer AI for next move
    2. Judge hit or miss
    3. Update Player board
    4. Update Computer score
    5. Inform Computer about result (for AI learning)

    Shooting does NOT generate AI logic.
*/
void Shooting::Update_Player_Grid(Computer& cpu) {

    // Step 1: Computer decides where to shoot
    pair<int,int> move = cpu.makeMove();

    int row = move.first;
    int col = move.second;

    bool hit = false;

    // Step 2: Judge hit or miss
    if (Board[row][col] == 1) {
        Board[row][col] = 3;      // Mark hit
        cout << "   Computer HIT!\n";
        Count_Computer++;
        hit = true;
    }
    else {
        Board[row][col] = 4;      // Mark miss
        cout << "   Computer MISS!\n";
    }

    cout << "   Computer shoots: "
         << char(row + 64) << col - 1 << endl;

    // Step 3: Inform AI about result
    cpu.markResult(row, col, hit);
}