/*
Created by Chwis Bijaisoradat  58090009  KMITL SE 07
Created using Visual Studio 2015
C++ project  Pacman clone game v 1.5
*/

#include <iostream>
#include <windows.h>
#include <string>
#include <stdbool.h>
#include <conio.h>
#include <thread>
#include <mutex>

using namespace std;

struct character {
	char direction = 0;
	int x = 0;
	int y = 15;
};

#define TRUE = 1;
#define FALSE = 0;
#define PACMAN_CHAR 60
#define BOT_CHAR 66

const int MAXROWS = 32;
const int MAXCOLUMNS = 28;
const int MAXBOT = 1;
const int wall = 35;
const int dots = 46;
const int blank = 000;
int pts = 0;
int addScoreNum = 10;
HANDLE  hConsole;
COORD coord;
mutex mtx;
int pacX = 0, pacY = 15;
int tmpX = 0, tmpY = 0;
char pacFlag = 0;
int botX[MAXBOT] = { 13 };
int botY[MAXBOT] = { 15 };
char Direction[] = { 'w','s','a','d' };
character pacman;
bool gameOver = false;
bool gameWin = false;
int difficulty;
int maxBot;

char level_classic[MAXROWS][MAXCOLUMNS] = {
	{ 35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35 },
	{ 35,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  35,  35,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  35 },
	{ 35,  46,  35,  35,  35,  35,  46,  35,  35,  35,  35,  35,  46,  35,  35,  46,  35,  35,  35,  35,  35,  46,  35,  35,  35,  35,  46,  35 },
	{ 35,  46,  35,  35,  35,  35,  46,  35,  35,  35,  35,  35,  46,  35,  35,  46,  35,  35,  35,  35,  35,  46,  35,  35,  35,  35,  46,  35 },
	{ 35,  46,  35,  35,  35,  35,  46,  35,  35,  35,  35,  35,  46,  35,  35,  46,  35,  35,  35,  35,  35,  46,  35,  35,  35,  35,  46,  35 },
	{ 35,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  35 },
	{ 35,  46,  35,  35,  35,  35,  46,  35,  35,  46,  35,  35,  35,  35,  35,  35,  35,  35,  46,  35,  35,  46,  35,  35,  35,  35,  46,  35 },
	{ 35,  46,  35,  35,  35,  35,  46,  35,  35,  46,  35,  35,  35,  35,  35,  35,  35,  35,  46,  35,  35,  46,  35,  35,  35,  35,  46,  35 },
	{ 35,  46,  46,  46,  46,  46,  46,  35,  35,  46,  46,  46,  46,  35,  35,  46,  46,  46,  46,  35,  35,  46,  46,  46,  46,  46,  46,  35 },
	{ 35,  35,  35,  35,  35,  35,  46,  35,  35,  35,  35,  35, 000,  35,  35, 000,  35,  35,  35,  35,  35,  46,  35,  35,  35,  35,  35,  35 },
	{ 35,  35,  35,  35,  35,  35,  46,  35,  35,  35,  35,  35, 000,  35,  35, 000,  35,  35,  35,  35,  35,  46,  35,  35,  35,  35,  35,  35 },
	{ 35,  35,  35,  35,  35,  35,  46,  35,  35, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000,  35,  35,  46,  35,  35,  35,  35,  35,  35 },
	{ 35,  35,  35,  35,  35,  35,  46,  35,  35, 000,  35,  000, 000, 000, 000, 000,  000,  35, 000,  35,  35,  46,  35,  35,  35,  35,  35,  35 },
	{ 35,  35,  35,  35,  35,  35,  46,  35,  35, 000,  35, 000, 000, 000, 000, 000, 000,  35, 000,  35,  35,  46,  35,  35,  35,  35,  35,  35 },
	{ 35,  35,  35,  35,  35,  35,  46,  35,  35, 000,  35, 000, 000, 000, 000, 000, 000,  35, 000,  35,  35,  46,  35,  35,  35,  35,  35,  35 },
	{ 67, 000, 000, 000, 000, 000, 46, 000, 000, 000,  35, 000, 000, 000, 000, 000, 000,  35, 000, 000, 000,  46, 000, 000, 000, 000, 000, 000 },
	{ 35,  35,  35,  35,  35,  35,  46,  35,  35, 000,  35, 000, 000, 000, 000, 000, 000,  35, 000,  35,  35,  46,  35,  35,  35,  35,  35,  35 },
	{ 35,  35,  35,  35,  35,  35,  46,  35,  35, 000,  35, 000, 000, 000, 000, 000, 000,  35, 000,  35,  35,  46,  35,  35,  35,  35,  35,  35 },
	{ 35,  35,  35,  35,  35,  35,  46,  35,  35, 000,  35,  000, 000, 000, 000, 000,  000,  35, 000,  35,  35,  46,  35,  35,  35,  35,  35,  35 },
	{ 35,  35,  35,  35,  35,  35,  46,  35,  35, 000, 000, 000, 000, 000, 000, 000, 000, 000, 000,  35,  35,  46,  35,  35,  35,  35,  35,  35 },
	{ 35,  35,  35,  35,  35,  35,  46,  35,  35, 000,  35,  35,  35,  35,  35,  35,  35,  35, 000,  35,  35,  46,  35,  35,  35,  35,  35,  35 },
	{ 35,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  35,  35,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  35 },
	{ 35,  46,  35,  35,  35,  35,  46,  35,  35,  35,  35,  35,  46,  35,  35,  46,  35,  35,  35,  35,  35,  46,  35,  35,  35,  35,  46,  35 },
	{ 35,  46,  35,  35,  35,  35,  46,  35,  35,  35,  35,  35,  46,  35,  35,  46,  35,  35,  35,  35,  35,  46,  35,  35,  35,  35,  46,  35 },
	{ 35,  46,  46,  46,  35,  35,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  35,  35,  46,  46,  46,  35 },
	{ 35,  35,  35,  46,  35,  35,  46,  35,  35,  46,  35,  35,  35,  35,  35,  35,  35,  35,  46,  35,  35,  46,  35,  35,  46,  35,  35,  35 },
	{ 35,  35,  35,  46,  35,  35,  46,  35,  35,  46,  35,  35,  35,  35,  35,  35,  35,  35,  46,  35,  35,  46,  35,  35,  46,  35,  35,  35 },
	{ 35,  46,  46,  46,  46,  46,  46,  35,  35,  46,  46,  46,  46,  35,  35,  46,  46,  46,  46,  35,  35,  46,  46,  46,  46,  46,  46,  35 },
	{ 35,  46,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  46,  35,  35,  46,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  46,  35 },
	{ 35,  46,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  46,  35,  35,  46,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  46,  35 },
	{ 35,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  46,  35 },
	{ 35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35,  35 }
};



void show_map() {
	printf("Score : %d\n", pts);
	for (int y = 0;y < 32;y++) {
		for (int x = 0;x < 28;x++) {
			printf("%c", level_classic[y][x]);
		}
		printf("\n");
	}
}

void addScore(int x, int y) {
	if (level_classic[y][x] == dots) {
		pts += addScoreNum;
	}
}


class player {
public:
	player();
	void gotoxy(int x, int y);
	void printxy(int x, int y, char ch);
	void pacmanMove(int old_x, int old_y, int new_x, int new_y);
	bool pacWalk();
};

player::player() {

}

void player::gotoxy(int x, int y) {
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hConsole, coord);
}

void player::printxy(int x, int y, char ch) {
	gotoxy(x, y + 1);
	printf("%c", ch);
}

void player::pacmanMove(int old_x, int old_y, int new_x, int new_y) {
	if (level_classic[new_y][new_x] != (char)wall) {
		addScore(new_x, new_y);
		level_classic[old_y][old_x] = blank;
		level_classic[new_y][new_x] = PACMAN_CHAR;
		printxy(old_x, old_y, blank);
		printxy(new_x, new_y, PACMAN_CHAR);
		pacman.x = new_x;
		pacman.y = new_y;
	}
}

bool player::pacWalk() {
	int tmpX = pacman.x;
	int tmpY = pacman.y;
	switch (pacman.direction) {
	case 'w':
		tmpY = tmpY - 1 < 0 ? MAXROWS - 1 : tmpY - 1;
		break;
	case 's':
		tmpY = (tmpY + 1) % MAXROWS;
		break;
	case 'a':
		tmpX = tmpX - 1 < 0 ? MAXCOLUMNS - 1 : tmpX - 1;
		break;
	case 'd':
		tmpX = (tmpX + 1) % MAXROWS;
		break;
	default:
		break;
	}
	pacmanMove(pacman.x, pacman.y, tmpX, tmpY);
	if (pts >= (248 * addScoreNum)) {
		return true;
	}
	else {
		return false;
	}
}

bool navigate(character &botIn, int &new_x, int &new_y) {
	int tmpX = botIn.x;
	int tmpY = botIn.y;
	switch (botIn.direction) {
	case 'w':
		tmpY = tmpY - 1 < 0 ? MAXROWS - 1 : tmpY - 1;
		break;
	case 's':
		tmpY = (tmpY + 1) % MAXROWS;
		break;
	case 'a':
		tmpX = tmpX - 1 < 0 ? MAXCOLUMNS - 1 : tmpX - 1;
		break;
	case 'd':
		tmpX = (tmpX + 1) % MAXROWS;
		break;
	default:
		break;
	}
	if (level_classic[tmpY][tmpX] != wall) {
		new_x = tmpX;
		new_y = tmpY;
		return true;
	}
	else {
		return false;
	}
}

class ghost:player {
public:
	void botMove(character &botIn, int new_x, int new_y);
	bool botWalk(character &botIn);
};

void ghost::botMove(character &botIn, int new_x, int new_y) {
	printxy(botIn.x, botIn.y, level_classic[botIn.y][botIn.x]);
	printxy(new_x, new_y, BOT_CHAR);
	botIn.x = new_x;
	botIn.y = new_y;
}


bool ghost::botWalk(character &botIn) {
	int tmpX = 0;
	int tmpY = 0;

	if (navigate(botIn, tmpX, tmpY) == false) {
		while (true) {
			int run = rand() % 4;
			botIn.direction = Direction[run] != botIn.direction ? Direction[run] : Direction[(run + 1) % 4];
			if (navigate(botIn, tmpX, tmpY) == true) {
				break;
			}
		}
	}

	if (level_classic[botIn.y][botIn.x] == (char)PACMAN_CHAR) {
		return true;
	}
	else if (level_classic[tmpY][tmpX] == (char)PACMAN_CHAR) {
		botMove(botIn, tmpX, tmpY);
		return true;
	}
	else {
		botMove(botIn, tmpX, tmpY);
		return false;
	}

}

void readKey() {
	while (true) {
		char directionInput = _getch();
		if (gameWin == true || gameOver == true) break;
		mtx.lock();
		int tmpX = pacman.x;
		int tmpY = pacman.y;
		switch (directionInput) {
		case 'w':
			tmpY = tmpY - 1 < 0 ? MAXROWS - 1 : tmpY - 1;
			break;
		case 's':
			tmpY = (tmpY + 1) % MAXROWS;
			break;
		case 'a':
			tmpX = tmpX - 1 < 0 ? MAXCOLUMNS - 1 : tmpX - 1;
			break;
		case 'd':
			tmpX = (tmpX + 1) % MAXROWS;
			break;
		default:
			break;
		}
		pacman.direction = level_classic[tmpY][tmpX] != wall ? directionInput : pacman.direction;
		mtx.unlock();
	}

}

void main() {
	player p1;
	ghost g;
	int speed = 200;
	cout << "---------------------------------------"<<endl;
	cout << "                                       "<<endl;
	cout << "    Welcome to Pacman clone v1.5       "<<endl;
	cout << "                                       "<<endl;
	cout << "---------------------------------------"<<endl;
	cout << "For best experience, enlarge the screen"<<endl;
	cout << "Instructions : WASD to control pacman, eat all dots while avoiding the bots to win!"<<endl;
	cout << "Enter difficulty (1-3 lower is easier) : ";
	cin >> difficulty;
	if (difficulty == 1) {
		maxBot = 2;
	}
	else if (difficulty == 2) {
		maxBot = 4;
	}
	else if (difficulty == 3) {
		maxBot = 6;
	}
	else if (difficulty == 4) {
		cout << "Expected an error? Too bad this is a hidden nightmare mode" << endl << "Its a little punishment sorry :D" << endl << endl;
		speed = 150;
		maxBot = 15;
	}
	else {
		cout << "Invalid input, difficulty will be set to 2" << endl;
		maxBot = 4;
	}
	cout << "The game will begin shortly after a 10 second delay";
	Sleep(10000);
	system("cls");
	srand(time(NULL));
	Sleep(2000);
	thread first(readKey); 
	show_map();
	char tmpPacFlag = 0;
	character bot[4];
	for (int i = 0; i < maxBot;i++) {
		bot[i].direction = Direction[i % 4];
		bot[i].x = 13;
		bot[i].y = 15;
	}
	while (true) {
		Sleep(speed);
		gameWin = p1.pacWalk();
		p1.gotoxy(0, 0);
		printf("                                           ");
		p1.gotoxy(0, 0);
		printf("Score: %d", pts);
		for (int i = 0; i < maxBot; i++) {
			gameOver = g.botWalk(bot[i]);
			if (gameOver == true)
			{
				break;
			}
		}

		if (gameOver == true || gameWin == true) break;
	}

	if (gameOver == true)
	{
		p1.gotoxy(0, 0);
		printf("GAMEOVER!! Score: %d\t", pts);
	}
	else if (gameWin == true) {
		system("cls");
		p1.gotoxy(30, 13);
		printf("You Win!! Score: %d\n", pts);
	}
	first.join();
	while (true) {
		_getch();
	}
}
