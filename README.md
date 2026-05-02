# Battleship Game (Text-Based C++ Version)

## Team Members

- Fang Yinqi
- Wu Canyu
- Li Xuanping

---

## Game Description

This project is a text-based Battleship game implemented in C++.  
The player competes against a computer-controlled AI on a 10x10 board.

Both sides randomly deploy fleets at the beginning of the game.  
Players take turns attacking coordinates until one side's fleet is completely destroyed.

The game runs entirely in the terminal.

---

## Game Features

- 10x10 game board
- Random ship placement
- Three difficulty levels:
  - Easy (Random AI)
  - Medium (Target-following AI)
  - Hard (Smart directional tracking AI)
- Turn-based gameplay
- Win/Loss detection
- Console board display
- Object-Oriented Design (multiple classes)

---

## Difficulty Levels

### 1. Easy Mode
The computer selects random coordinates that have not been attacked before.

### 2. Medium Mode
When the computer hits a ship, it stores neighboring cells and tries them next.

### 3. Hard Mode
After two successful hits, the computer locks direction and continues attacking in that direction until the ship is destroyed.

---

## Coding Requirements Fulfilled

### 1. Generation of Random Events

- Ships are randomly placed using `rand()`.
- Computer attacks randomly in Easy mode.
- Random placement and move selection ensure different gameplay each run.

### 2. Data Structures

- `std::vector<std::vector<int>>` is used to represent the game boards.
- `std::vector<int>` stores ship lengths.
- `std::vector<std::pair<int,int>>` stores AI targets and hit history.

### 3. Dynamic Memory Management

- The game uses `std::vector`, which dynamically manages memory internally.
- Boards are resized dynamically based on board size.

### 4. Program Organized into Multiple Files

The program is divided into:

- `main.cpp`
- `player.cpp / player.h`
- `computer.cpp / computer.h`
- `shooting.cpp / shooting.h`
- `Makefile`

Each class has clear responsibilities:
- `Player` handles player board and ship placement.
- `Computer` handles AI logic and board management.
- `Shooting` manages turns and board display.
- `main` controls game flow.

### 5. Object-Oriented Programming

- Encapsulation of logic inside classes.
- Private and public member separation.
- Clear separation of responsibilities.

---

## Compilation Instructions

To compile the project: