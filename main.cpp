#include <iostream>
#include <ctime>
#include <cstdlib>

#include "Player.h"
#include "Computer.h"
#include "Shooting.h"

using namespace std;

/* ================= Clear Screen ================= */
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/* ================= Title ================= */
void showTitle() {

    cout << "\n\n";
    cout << "=============================================================================\n";
    cout << "                                                                             \n";
    cout << "   ██████╗  █████╗ ████████╗████████╗██╗     ███████╗███████╗██╗  ██╗██╗██████╗ \n";
    cout << "   ██╔══██╗██╔══██╗╚══██╔══╝╚══██╔══╝██║     ██╔════╝██╔════╝██║  ██║██║██╔══██╗\n";
    cout << "   ██████╔╝███████║   ██║      ██║   ██║     █████╗  ███████╗███████║██║██████╔╝\n";
    cout << "   ██╔══██╗██╔══██║   ██║      ██║   ██║     ██╔══╝  ╚════██║██╔══██║██║██╔═══╝ \n";
    cout << "   ██████╔╝██║  ██║   ██║      ██║   ███████╗███████╗███████║██║  ██║██║██║     \n";
    cout << "   ╚═════╝ ╚═╝  ╚═╝   ╚═╝      ╚═╝   ╚══════╝╚══════╝╚══════╝╚═╝  ╚═╝╚═╝╚═╝     \n";
    cout << "                                                                             \n";
    cout << "=============================================================================\n";
    cout << "\n";
    cout << "                             ⚓  BATTLESHIP  ⚓\n";
    cout << "\n\n";
}

int main() {

    srand(static_cast<unsigned int>(time(nullptr)));

    clearScreen();
    showTitle();

    /* ================= Difficulty ================= */

    cout << "                              Select Difficulty\n";
    cout << "-----------------------------------------------------------------------------\n\n";
    cout << "               1  →  Easy     (Random AI)\n\n";
    cout << "               2  →  Medium   (Target AI)\n\n";
    cout << "               3  →  Hard     (Smart Tracking AI)\n\n";
    cout << "-----------------------------------------------------------------------------\n\n";
    cout << "               Enter choice (1-3): ";

    int difficulty;
    cin >> difficulty;

    if(difficulty < 1 || difficulty > 3) {
        cout << "\n               Invalid choice. Defaulting to Easy.\n";
        difficulty = 1;
    }

    cout << "\n\n               Deploying fleets...\n";
    cout << "               Preparing battlefield...\n\n";

    Player player;
    Computer cpu(10, difficulty);
    Shooting game;

    player.placeShips();
    cpu.placeAllShips();

    cout << "               Fleets ready for battle.\n";
    cout << "\n               Press Enter to begin...";
    cin.ignore();
    cin.get();

    int round = 1;

    /* ================= Game Loop ================= */

    while(true) {

        clearScreen();
        showTitle();

        cout << "                                  ROUND "
             << round << "\n";
        cout << "-----------------------------------------------------------------------------\n\n";

        game.drawBoards(player, cpu);

        cout << "\n\n============================== YOUR TURN ====================================\n\n";
        game.playerTurn(player, cpu);

        if(cpu.allShipsDestroyed()) {
            cout << "\n\n                       🏆  YOU WIN THE WAR!  🏆\n\n";
            break;
        }

        cout << "\n\n============================ COMPUTER TURN ==================================\n\n";
        game.computerTurn(player, cpu);

        if(player.allShipsDestroyed()) {
            cout << "\n\n                      💀  YOUR FLEET HAS FALLEN  💀\n\n";
            break;
        }

        round++;

        cout << "\n\n                        Press Enter for next round...";
        cin.ignore();
        cin.get();
    }

    /* ================= Final Board ================= */

    cout << "\n\n=============================================================================\n";
    cout << "                              FINAL BATTLEFIELD\n";
    cout << "=============================================================================\n\n";

    game.drawBoards(player, cpu);

    cout << "\n\n                              GAME OVER\n\n";
    cout << "=============================================================================\n\n";

    return 0;
}