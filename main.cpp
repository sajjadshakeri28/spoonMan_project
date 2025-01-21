#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <windows.h>

using namespace std;

const int MAP_SIZE = 25;
char gameMap[MAP_SIZE][MAP_SIZE];
int playerX = 0, playerY = 0;
bool gateVisible = false;
int difficulty = 1;
int moves = 0 , bombsUsed = 0;
clock_t startTime;

struct Bomb {
    int x, y;
    int timer;
};

vector<Bomb> bombs;

void gotoxy(int x , int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color)
{
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


void mainMenu();
void startGame();
void initializeMap();
void setDifficulty();
void printMap();
void movePlayer(char input);
void placeBomb();
void updateBombs();
void explodeBomb(int index);
void checkEnemies();
void showGate();
void checkGameEnd();
int calculateScore();
