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
void startGame() {
    startTime = clock();
    moves = 0;
    bombsUsed = 0;
    initializeMap();
    char input;
    while (true) {
        system("cls");
        printMap();

        cout << "Controls: W = Up, S = Down, A = Left, D = Right, B = Place Bomb, Q = Quit" << endl;
        cout << "Enter your move: ";
        input = getch();

        if (input == 'q' || input == 'Q') {
            cout << "Returning to main menu..." << endl;
            break;
        } else if (input == 'b' || input == 'B') {
            placeBomb();
        } else {
            movePlayer(input);
        }

        updateBombs();
        checkEnemies();
        checkGameEnd();
    }void printMap() {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {

            switch(gameMap[i][j])
            {
                case 'S':
                    setColor(10);
                    break;
                case 'E':
                    setColor(12);
                    break;
                case 'X':
                    setColor(8);
                    break;
                case '-':
                    setColor(6);
                    break;
                case 'B':
                    setColor(14);
                    break;
                case '#':
                    setColor(9);
                    break;
                default:
                    setColor(15);
                    break;

            }
            cout << gameMap[i][j] << " ";
        }
        cout << endl;
    }
}

}
void initializeMap() {
    srand(time(0));
    int brickwallRate, enemyRate;

    if(difficulty == 1)
    {
        brickwallRate = 4;
        enemyRate = 18 ;
    }
    else if(difficulty == 2)
    {
        brickwallRate = 3;
        enemyRate = 12;
    }
    else{
        brickwallRate = 2;
        enemyRate = 8;
    }
    gateVisible = false;
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (i == 0 || i == MAP_SIZE - 1 ||  j == 0 || j == MAP_SIZE - 1) {
                gameMap[i][j] = '*';
            } else if (( i ) % 2 == 0 && ( j ) % 2 == 0) {
                gameMap[i][j] = 'X';
            } else if ((rand() % brickwallRate) == 0) {
                gameMap[i][j] = '-';
            } else if ((rand() % enemyRate) == 0) {
                gameMap[i][j] = 'E';
            } else {
                gameMap[i][j] = ' ';
            }
        }
    }

    playerX = 1;
    playerY = 1;
    gameMap[playerX][playerY] = 'S';
}
