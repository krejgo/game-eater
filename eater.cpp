#include <iostream>
#include <unistd.h>
#include <conio.h>
#include <windows.h>
#include <vector>
using namespace std;

const int border	= GetPrivateProfileInt("Settings", "border", 78, "./settings.ini");
const int dropdown	= GetPrivateProfileInt("Settings", "dropRange", 60, "./settings.ini");
int ph1L			= GetPrivateProfileInt("Settings", "ph1L", 4, "./settings.ini");
int ph2L			= GetPrivateProfileInt("Settings", "ph2L", 2, "./settings.ini");
const int K_UP 		= 72;
const int K_DOWN 	= 107;
const int K_LEFT 	= 106;
const int K_RIGHT 	= 108;

//==============CLASSES============//
#include "player.h"
#include "level.h"

//===========-SUBPROGRAMS==========//
void display (int space);

//===========MAIN PROGRAM==========//
int main() {
	int input;
	level game;

	cout << "Insert snake's length : ";
	cin >> input;
	
	player snake(input);
	game.setPlayer(&snake);
	
	while(1) {

		if (kbhit()) {
			switch (getch()) {
				case K_RIGHT :
					cKey = 1; break;
				case K_DOWN :
					cKey = 0; break;
				case K_LEFT :
					cKey = -1; break;
			}
		}

		game.updateFrame();
		snake.updatePos();

		usleep(25000); // 40 fps
	}
	
	return 0;
}

//===========SUBPROGRAMS SOURCE==========//
void display (int space) {
	cout << string(space, ' ') << '*' << endl;
}
