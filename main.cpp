#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <windows.h>
#include <string>
#include <fstream>

using namespace std;

const int MAP_SIZE = 25;
char gameMap[MAP_SIZE][MAP_SIZE];
int playerX = 0, playerY = 0;
bool gateVisible = false;
int difficulty = 1;
int moves = 0 , bombsUsed = 0;
clock_t startTime;
string playerName;
bool hasAbillity = false;


struct Bomb {
    int x, y;
    int timer;
};
struct Score{
    string name;
    int score;
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
void showHighscores();
void saveScore(int score);

int main() {
    mainMenu();
    setDifficulty();
    calculateScore();
    return 0;
}

void mainMenu() {
    cout << "please Enter your name:";
    cin >> playerName;
    int choice;
    do {
        cout << "======== SpoonMan ========" << endl;
        cout << "1. Start Game" << endl;
        cout << "2. Difficulty" << endl;
        cout << "3. Help" << endl;
        cout << "4. High Scores" << endl;
        cout << "5. Exit" << endl;
        cout << "==========================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        system("cls");
        switch (choice) {
            case 1:
                startGame();
                break;
            case 2:
                cout << "Setting difficulty..." << endl;
                setDifficulty();
                break;
            case 3:
                cout << "teem name:mahad" << endl;
                cout << "team member:\nmahdiAmini:4031226239\nsajjadshakeri:4031226081" << endl;
                cout << "Help: Your goal is to defeat all enemies and exit the map." << endl;
                cout << "Controls: W = Up, S = Down, A = Left, D = Right, B = Place Bomb, Q = Quit" << endl;
                break;
            case 4:
                cout << "High Scores: " << endl;
                showHighscores();
                break;
            case 5:
                cout << "Exiting game..." << endl;
                system("cls");
                exit(0);
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 5);
}
void startGame()
 {
    startTime = clock();
    moves = 0;
    bombsUsed = 0;
    hasAbillity = false;
    initializeMap();
    char input;
    while (true) {
        system("cls");
        printMap();
        cout << "Enter your move: ";
        input = getch();

        if (input == 'q'||  input == 'Q') {
            cout << "Returning to main menu..." << endl;
            break;
        } else if (input == 'b'||  input == 'B') {
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
        brickwallRate =7;
        enemyRate = 18 ;
    }
    else if(difficulty == 2)
    {
        brickwallRate = 6;
        enemyRate = 16;
    }
    else{
        brickwallRate = 5;
        enemyRate = 12;
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

    for(int i = 1 ; i <= 2 ; i++)
    {
        gameMap[playerX + i][playerY] = ' ';
        gameMap[playerX][playerY + i] = ' ';
    }
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
        case 'w': case 'W':
            newX--; break;
        case 's': case 'S':
            newX++; break;
        case 'a': case 'A':
            newY--; break;
        case 'd': case 'D':
            newY++; break;
        default: cout << "Invalid move!" << endl; return;
    }

    if (gameMap[newX][newY] == '*' || gameMap[newX][newY] == 'X' || gameMap[newX][newY] == '-') {
        cout << "You hit a wall!" << endl;
        return;
    }
    if(gameMap[newX][newY] == 'A')
    {
        hasAbillity = true;
        cout << "Abillity collected! bomb radius increased!" << endl;
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
    int bombTimer = hasAbillity ? 4 : 3;
    Bomb bomb = {playerX, playerY,bombTimer};
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

}
void explodeBomb(int index) {
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
    int radius = 0;
    if(hasAbillity)
        radius = 2;
    else
        radius = 1;
    for (int i = 1; i <= radius; i++) {

        if (gameMap[x - i][y] != 'X' && gameMap[x - i][y] != '*')

            if(hasAbillity)
            {
                gameMap[x - i][y] = ' ';
            }
            else
            {
                if(gameMap[x - i][y] == '-')
                    gameMap[x - i][y] = (rand() % 5 == 0) ? 'A' : ' ' ;
            }
        if (gameMap[x + i][y] != 'X' && gameMap[x + i][y] != '*')
           if(hasAbillity)
           {
                gameMap[x + i][y] = ' ';
           }
            else
            {
                if(gameMap[x + i][y] == '-')
                    gameMap[x + i][y] = (rand() % 5 == 0) ? 'A' : ' ' ;
            }
        if (gameMap[x][y - i] != 'X' && gameMap[x][y - i] != '*')
            if(hasAbillity)
            {

                gameMap[x][y - i] = ' ';
            }
         else
            {
                if(gameMap[x][y - i] == '-')
                    gameMap[x][y - i] = (rand() % 5 == 0) ? 'A' : ' ';

            }
        if (gameMap[x][y + i] != 'X' && gameMap[x][y + i] != '*')
            if(hasAbillity)
            {
                 gameMap[x][y + i] = ' ';
            }
         else
            {
                if(gameMap[x][y + i] == '-')
                    gameMap[x][y + i] = (rand() % 5 == 0) ? 'A' : ' ';
            }
    }
    cout << "Boom! Bomb exploded at (" << x << ", " << y << ")." << endl;
}
void checkEnemies()
{
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
        string answer;
    if (gateVisible && playerX == MAP_SIZE - 2 && playerY == MAP_SIZE - 2) {
        system("cls");
        int finalscore = calculateScore();
        cout << "Congratulations!"<< playerName << "You reached the gate and completed the game!" << endl;
        cout << "yourscore:" << finalscore << endl;
        saveScore(finalscore);
        cout << "are you want to play again?(yes/no)"<< endl;
        cin >> answer;
        if(answer == "yes")
        {
             mainMenu();
        }
       else if(answer == "no")
       {
        system("cls");
        exit(0);
       }

    }
}

void saveScore(int score)
{
    ofstream file("highscores.txt",ios::app);

    if(!file)
    {
        cout << "Eror : could not open higscores.txt for writing" << endl;
        return;
    }
    file << playerName << " " << score << endl;
    file.close();
}
void showHighscores()
{
    Score scores[100];
    int scorecount = 0;


    ifstream file("highscores.txt");

    if(file.is_open())
    {
        while(file >> scores[scorecount].name >> scores[scorecount].score)
        {
            ++scorecount;
            if(scorecount >= 100)
            {
                break;
            }
        }
    file.close();
    }
    else{
        cout << "No high scores availbe." << endl;
        return;
    }

    for(int i = 0 ; i < scorecount - 1 ; i++)
    {
        for(int j = 0 ; j < scorecount - i - 1 ; j++)
        {
            if(scores[j].score < scores[j+1].score)
            {
                Score temp = scores[i];
                scores[j]= scores[j+1];
                scores[j+1]= temp;

            }
        }
    }

    cout << "=======HighScores=======" << endl;
    for(int i = 0 ; i < scorecount && i < 10 ; i++)
    {
        cout << i + 1 << "_" << scores[i].name << "-" << scores[i].score<< endl;
        cout << "============================";
        system("pause");
    }
}
