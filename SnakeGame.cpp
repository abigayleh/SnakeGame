#include <iostream>
using namespace std;
#include <conio.h>;

bool gameOver;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score;
//Max of 100 tail pieces
int tailX[100], tailY[100];
//Number of tail pieces
int nTail;
enum eDirection { STOP = '0', LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
	gameOver = false;
	dir = STOP;
	score = 0;

	//Snake starts in middle of map
	x = width / 2;
	y = height / 2;
	// Random number from 0 to width-1
	fruitX = rand() % width;
	fruitY = rand() % height;
}

void Draw() {

	//Clears screen
	system("cls");
	//Top wall
	for (int i = 0; i < width; i++)
		cout << "-";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			// To get side walls (j = 0 and j = width-1)
			if (j == 0)
				cout << "|";
			else if (j == width-1)
				cout << "|";
			else if (i == y and j == x)
				cout << "O";
			else if (i == fruitY and j == fruitX)
				cout << "X";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j and tailY[k] == i) {
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
		}
		cout << endl;
	}

	//Bottom wall
	for (int i = 0; i < width; i++)
		cout << "-";
	cout << endl;

	cout << "Score: " << score << endl;

}

void Input() {

	//Positive if keyboard is pressed, 0 if nothing is pressed
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's': 
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}

}

void Logic() {

	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir) {
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
	if (x >= width or x < 0 or y >= height or y < 0)
		gameOver = true;
	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x and tailY[i] == y)
			gameOver = true;
	}
	if (x == fruitX and y == fruitY) {
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}

int main() {
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
	}
	return 0;
}