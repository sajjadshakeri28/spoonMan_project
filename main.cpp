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

int main() {
    mainMenu();
    setDifficulty();
    calculateScore();
    return 0;
}


void mainMenu() {
    int choice;
    do {
        cout << "======== SpoonMan ========" << endl;
        cout << "1. Start Game" << endl;
        cout << "2. Load Game" << endl;
        cout << "3. Difficulty" << endl;
        cout << "4. Help" << endl;
        cout << "5. High Scores" << endl;
        cout << "6. Exit" << endl;
        cout << "==========================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        system("cls"); 
        switch (choice) {
            case 1:
                startGame();
                break;
            case 2:
                cout << "Loading game..." << endl;
                break;
            case 3:
                cout << "Setting difficulty..." << endl;
                setDifficulty();
                break;
            case 4:
                cout << "Help: Your goal is to defeat all enemies and exit the map." << endl;
                break;
            case 5:
                cout << "High Scores: (Not implemented yet)" << endl;
                break;
            case 6:
                cout << "Exiting game..." << endl;
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 6);
}
