#ifndef __SHOOTING__
#define __SHOOTING__

#include <string>
#include "Computer.h"
#include "Player.h"

using namespace std;

// Global score counters shared across the program
extern int Count_Player;
extern int Count_Computer;

/*
    Shooting class responsibility:

    - Handles player shooting input
    - Executes shooting logic (judge hit or miss)
    - Updates both boards after shots
    - Displays both boards
    - Communicates shooting results to Computer AI

    Shooting DOES NOT:
    - Generate AI decisions
    - Store AI logic
    - Store attack history
*/
class Shooting {
private:
    int x, y;          // Current shooting coordinates
    string Cord;       // Raw coordinate input from user

    // Validates that a coordinate is within the playable 10x10 area
    bool isValidCoord(int row, int col);

public:
    Shooting();
    ~Shooting();

    // Reads and validates player shooting input
    void Input_Coord();

    // Draws both Player and Computer boards
    void Draw_Shooting();

    // Executes player's attack on Computer board
    void Update_Computer_Grid();

    // Executes Computer's attack on Player board
    // Uses Computer object only for AI decision and feedback
    void Update_Player_Grid(Computer& cpu);
};

#endif