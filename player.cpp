#include "Player.h"
#include <iostream>
#include <string>
#include <cctype>

using namespace std;


int Board[EIL + 1][STULP + 1] = { 0 };

Player::Player()
{
	Cord = "";
	pos = ' ';
	x = 0;
	y = 0;
}
Player::Player(int a, int b, string c, char d)
{
	x = a;
	y = b;
	Cord = c;
	pos = d;
}
Player::~Player() {} 

void Player::Draw_Board()
{
	cout << "                   Player\n            0 1 2 3 4 5 6 7 8 9\n";
	char letter = 'A';

	for (int i = 1; i < EIL - 1; i++) {
		cout << "          " << letter++ << " ";
		for (int j = 1; j < STULP - 1; j++) {

			if (Board[i][j] == 0 || Board[i][j] == 2) 
				cout << ". ";
			else if (Board[i][j] == 1) 
				cout << "0 ";
		}
		cout << endl;
	}
}
void Player::Input_Coord()
{
	bool correct_cord;

	do {
		cout << "   Input a coordinates X & Y (Ex.: A5): ";
		cin >> Cord;

		
		correct_cord = false;

		if (Cord.size() >= 2) { 
			char row = toupper(Cord[0]);
			x = row - ('A' - 1); 
			y = Cord[1] - ('0' - 1); 

			if (row >= 'A' && row <= 'J') { 
				correct_cord = true;
			}

			if (!(isdigit(Cord[1]))) { 
				correct_cord = false; 
			}
		}
	} while (!(correct_cord));
}
void Player::Input_Pos()
{
	do {
		cout << "   Enter position H/V: ";
		cin >> pos;
		pos = toupper(pos);

		if ((pos == 'V') || (pos == 'H')) break;
	} while (true);
}
void Player::Update_Coord(int i)
{
	bool repeat_input = false;
	
	Input_Coord();
	if (i < 7) Input_Pos();

	while (true) {
		if (Board[x][y] == 0) { 

			if (i > 6) { 
				Board[x][y] = 1; 
				break;
			}
			
			
			break;
		}
		else { 
			Input_Coord();
			if (i < 7) Input_Pos(); 
		}
	}

	if (i < 7)
		while (true) { 
			repeat_input = false;

			
			if (Board[x][y] != 0) {
				repeat_input = true;
			}
			else if (pos == 'V') { 
				if (i == 1) {
					if (x < 8) { 
						if (Board[x+1][y] == 0 && Board[x+2][y] == 0 && Board[x+3][y] == 0) { 
							Board[x][y] = 1;
							Board[x+1][y] = 1;
							Board[x+2][y] = 1;
							Board[x+3][y] = 1;
							break;
						}
						else repeat_input = true;
					}
					else repeat_input = true;
				}
				else if (i >= 2 && i < 4) {
					if (x < 9) { 
						if (Board[x+1][y] == 0 && Board[x+2][y] == 0) {
							Board[x][y] = 1;
							Board[x+1][y] = 1;
							Board[x+2][y] = 1;
							break;
						}
						else repeat_input = true;
					}
					else repeat_input = true;
				}
				else if (i > 3 && i < 7) {
					if (x < 10) { 
						if (Board[x+1][y] == 0) {
							Board[x][y] = 1;
							Board[x+1][y] = 1;
							break;
						}
						else repeat_input = true;
					}
					else repeat_input = true;
				}
			}
			else if (pos == 'H') { 
				if (i == 1) {
					if (y < 8) { 
						if (Board[x][y+1] == 0 && Board[x][y+2] == 0 && Board[x][y+3] == 0) { 
							Board[x][y] = 1;
							Board[x][y+1] = 1;
							Board[x][y+2] = 1;
							Board[x][y+3] = 1;
							break;
						}
						else repeat_input = true;
					}
					else repeat_input = true;
				}
				else if (i >= 2 && i < 4) {
					if (y < 9) { 
						if (Board[x][y+1] == 0 && Board[x][y+2] == 0) {
							Board[x][y] = 1;
							Board[x][y+1] = 1;
							Board[x][y+2] = 1;
							break;
						}
						else repeat_input = true;
					}
					else repeat_input = true;
				}
				else if (i > 3 && i < 7) {
					if (y < 10) { 
						if (Board[x][y+1] == 0) {
							Board[x][y] = 1;
							Board[x][y+1] = 1;
							break;
						}
						else repeat_input = true;
					}
					else repeat_input = true;
				}
			}

			if (repeat_input) {
				Input_Coord();
				if (i < 7) Input_Pos(); 
			}
		}

	
	int tempX = x, tempY = y;
	for (int p = 0; p < 4; p++) {
		
		for (int dx = -1; dx <= 1; dx++) {
			for (int dy = -1; dy <= 1; dy++) {
				int nx = tempX + dx;
				int ny = tempY + dy;
				if (nx >= 0 && nx <= EIL && ny >= 0 && ny <= STULP) {
					if (Board[nx][ny] == 0) Board[nx][ny] = 2;
				}
			}
		}

		if (tempX + 1 <= EIL && Board[tempX + 1][tempY] == 1) tempX++;
		else if (tempY + 1 <= STULP && Board[tempX][tempY + 1] == 1) tempY++;
		else break;
	}
}
