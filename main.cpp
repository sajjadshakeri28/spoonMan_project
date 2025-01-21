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
