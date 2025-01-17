#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main() {
    srand(time(0));

    gotoXY(30, 1);
    cout << "Hello to game" << endl << endl;

    gotoXY(3, 5);
    setColor(10);
    cout << "SS";

    for (int i = 9; i < 60; i += 6) {
        for (int j = 5; j < 20; j += 4) {
            setColor(8);
            gotoXY(i, j);
            cout << "XX";
        }
    }

    for (int i = 5; i < 60; i += 6) {
        for (int j = 5; j < 20; j += 2) {
            setColor(15);
            gotoXY(i, j);
            cout << "|  |";
        }
    }

   

