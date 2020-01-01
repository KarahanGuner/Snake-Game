#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[150], tailY[150];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
eDirection pDir;

void Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
void Draw() {
	system("cls");
	for (int i = 0; i < width; i++) {
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) {
				cout << "#";
			}
			if (i == y && j == x) {
				cout << "0";
			}
			else if (i == fruitY && j == fruitX) {
				cout << "F";
			}
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
					}
				}
				if (!print) {
					cout << " ";
				}
			}

		}
		cout << endl;
	}

	for (int i = 0; i < width; i++) {
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}
void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			if (dir == RIGHT) {
				break;
			}
			dir = LEFT;
			break;
		case 'd':
			if (dir == LEFT) {
				break;
			}
			dir = RIGHT;
			break;
		case 'w':
			if (dir == DOWN) {
				break;
			}
			dir = UP;
			break;
		case 's':
			if (dir == UP) {
				break;
			}
			dir = DOWN;
			break;
		case 'A':
			if (dir == RIGHT) {
				break;
			}
			dir = LEFT;
			break;
		case 'D':
			if (dir == LEFT) {
				break;
			}
			dir = RIGHT;
			break;
		case 'W':
			if (dir == DOWN) {
				break;
			}
			dir = UP;
			break;
		case 'S':
			if (dir == UP) {
				break;
			}
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void Logic() {

	for (int i = nTail; i > 0; i--) {
		tailX[i] = tailX[i - 1]; //i+1, i'nin eski hali, i, i-1'in eski hali oluyo
		tailY[i] = tailY[i - 1];
	}
	tailX[0] = x; //0 x'in eski hali oluyo x yeni haline alttaki switch statement'da geçiyo
	tailY[0] = y; //0 hiç meyve almasam da var ama yukardaki draw function'ı nTail en azından 1 olmadan artmasına izin vermiyor
				  //yani koordinat değerleri bir fruit ilerden gidiyor, ama draw function bu değeri çizmediği için sıkıntı yok
	
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	//if (x > width || x < 0 || y > height || y < 0) {
	//	gameOver = true;
	//}
	if (x >= width - 1) x = 0;
	else if (x < 0) x = width - 2;
	if (y >= height) y = 0;
	else if (y < 0) y = height - 1;

	for (int i = nTail; i > 0; i--) {
		if (tailX[i] == x && tailY[i] == y) {
			gameOver = true;
		}
	}
	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}
int main()
{
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		Sleep(30);
	}
	return 0;
}
