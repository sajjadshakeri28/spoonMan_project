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
void startGame()
 {
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
    }
}
void printMap()
{
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
void setDifficulty()
{
    cout << "Choose the degree of difficulty:" << endl;
    cout << "1.easy\n2.medium\n3.hard" << endl;
    cin >> difficulty;
}
int  calculateScore()
{
    int W_T = 1;
    float W_M = 0.5;
    int W_B = 2;
    double T = (double)(clock() - startTime) / CLOCKS_PER_SEC;
    int M= moves;
    int B = bombsUsed;
    double score= 100000/ (1 + (W_T * T) + (W_M * M) + (W_B * B));

    if(difficulty == 2)
    {
        score *= 1.2;
    }
    if(difficulty == 3)
    {
        score *= 1.3;
    }

    return score;
}
void movePlayer(char input) {
    int newX = playerX, newY = playerY;

    switch (input) {
        case 'w': case 'W': newX--; break;
        case 's': case 'S': newX++; break;
        case 'a': case 'A': newY--; break;
        case 'd': case 'D': newY++; break;
        default: cout << "Invalid move!" << endl; return;
    }

    if (gameMap[newX][newY] == '*' || gameMap[newX][newY] == 'X' || gameMap[newX][newY] == '-') {
        cout << "You hit a wall!" << endl;
        return;
    }

    if (gameMap[newX][newY] == 'E') {
        system("cls");
        cout << "GAME OVER!"<< endl;
        cout <<"You were caught by an enemy." << endl;
        cout << "if you want to get score: " << endl;
        mainMenu();
        exit(0);
    }

    gameMap[playerX][playerY] = ' ';
    playerX = newX;
    playerY = newY;
    gameMap[playerX][playerY] = 'S';
    moves++;
}
void placeBomb() {
    Bomb bomb = {playerX, playerY, 3};
    bombs.push_back(bomb);
    gameMap[playerX][playerY] = 'B';
    cout << "Bomb placed!" << endl;
    bombsUsed++;
}


void updateBombs() {
    for (int i = 0; i < bombs.size(); i++) {
        bombs[i].timer--;

        if (bombs[i].timer == 0) {
            explodeBomb(i);
            bombs.erase(bombs.begin() + i);
            i--;
        }
    }

}void explodeBomb(int index) {
    int x = bombs[index].x;
    int y = bombs[index].y;

    gameMap[x][y] = ' ';
    if ((playerX == x) && (playerY == y))
        {
            system("cls");
           cout << "GAME OVER!"<< endl;
           cout <<"You were caught by an enemy." << endl;
           cout << "if you want to get score: " << endl;
           mainMenu();
           exit(0);
        }
    for (int i = 1; i <= 1; i++) {
        if (gameMap[x - i][y] != 'X' && gameMap[x - i][y] != '*')
            gameMap[x - i][y] = ' ';
        if (gameMap[x + i][y] != 'X' && gameMap[x + i][y] != '*')
            gameMap[x + i][y] = ' ';
        if (gameMap[x][y - i] != 'X' && gameMap[x][y - i] != '*')
            gameMap[x][y - i] = ' ';
        if (gameMap[x][y + i] != 'X' && gameMap[x][y + i] != '*')
            gameMap[x ][y + i] = ' ';
       
    }
    cout << "Boom! Bomb exploded at (" << x << ", " << y << ")." << endl;
}


void checkEnemies() {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (gameMap[i][j] == 'E') {
                return;
            }
        }
    }
    if (!gateVisible) {
        showGate();
    }
}
void showGate() {
    gateVisible = true;
    gameMap[MAP_SIZE - 2][MAP_SIZE - 2] = '#';
    cout << "The gate has appeared!" << endl;
}

void checkGameEnd() {
    if (gateVisible && playerX == MAP_SIZE - 2 && playerY == MAP_SIZE - 2) {
        system("cls");
        cout << "Congratulations! You reached the gate and completed the game!" << endl;
        cout << "your Score: "<< calculateScore() << endl;
        cout << "if you want to get more score: " << endl;
        mainMenu();
        exit(0);
    }
}
