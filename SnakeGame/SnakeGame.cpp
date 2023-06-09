#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

struct SnakeSetup {
	const int width = 40;
	const int height = 20;
	bool gameover = false;
	int x = width / 2,
		y = height / 2,
		fruit_x = rand() % width,
		fruit_y = rand() % height,
		score = 0;
	int tail_x[100], tail_y[100];
	int n_tail = 0;
	enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
	eDirection dir = STOP;
};

void Draw(SnakeSetup& snake) {
	system("cls");
	for (int i = 0; i < snake.width + 2; ++i)
		cout << "#";
	cout << endl;
	
	for (int i = 0; i < snake.height; ++i) {
		for (int j = 0; j < snake.width; ++j) {
			if (j == 0)
				cout << "#";
			if (i == snake.y && j == snake.x)
				cout << "0";
			else if (i == snake.fruit_y && j == snake.fruit_x)
				cout << "F";
			else {
				bool print = false;
				for (int k = 0; k < snake.n_tail; ++k) {
					if (snake.tail_x[k] == j && snake.tail_y[k] == i) {
						cout << 'o';
						print = true;
					} 
				}
				if(!print) {
					cout << ' ';
				}
			}
			if (j == snake.width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < snake.width + 2; ++i)
		cout << "#";
	cout << endl;
	cout << "Score: " << snake.score << endl;
}

void Input(SnakeSetup& snake) {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			snake.dir = snake.LEFT;
			break;
		case 'd':
			snake.dir = snake.RIGHT;
			break;
		case 'w':
			snake.dir = snake.UP;
			break;
		case 's':
			snake.dir = snake.DOWN;
			break;
		case 'x':
			snake.gameover = true;
			break;
		}
	}
}

void Logic(SnakeSetup& snake) {
	int prev_x = snake.tail_x[0];
	int prev_y = snake.tail_y[0];
	int prev_2x, prev_2y;
	snake.tail_x[0] = snake.x;
	snake.tail_y[0] = snake.y;
	for (int i = 1; i < snake.n_tail; ++i) { //tail "moving"
		prev_2x = snake.tail_x[i];
		prev_2y = snake.tail_y[i];
		snake.tail_x[i] = prev_x;
		snake.tail_y[i] = prev_y;
		prev_x = prev_2x;
		prev_y = prev_2y;
	}

	switch (snake.dir)
	{
	case snake.LEFT:
		snake.x--;
		break;
	case snake.RIGHT:
		snake.x++;
		break;
	case snake.UP:
		snake.y--;
		break;
	case snake.DOWN:
		snake.y++;
		break;
	default:
		break;
	}

	//if (snake.x > snake.width || snake.x < 0 || snake.y > snake.height ||snake.y < 0) { //hiting-wall mode
	//	snake.gameover = true;
	//} 
	if (snake.x >= snake.width) snake.x = 0;  //unhiting-wall mode
	else if (snake.x < 0) snake.x = snake.width - 1;
	if (snake.y >= snake.height) snake.y = 0;
	else if (snake.y < 0) snake.y = snake.height - 1;

	for (int i = 0; i < snake.n_tail; ++i) { //tail-hiting
		if (snake.tail_x[i] == snake.x && snake.tail_y[i] == snake.y)
			snake.gameover = true;
	}
	if (snake.x == snake.fruit_x && snake.y == snake.fruit_y) { //fruit-eating
		snake.score += 10;
		snake.fruit_x = rand() % snake.width;
		snake.fruit_y = rand() % snake.height;
		++snake.n_tail;
	}
}

int main()
{
	SnakeSetup snake;
	while (!snake.gameover) {
		Draw(snake);
		Input(snake);
		Logic(snake);
		Sleep(100);
	}
	system("cls");
	cout << "Good! You are complete the game!" << endl;
	cout << "Your score: " << snake.score << endl;
	//Sleep();
	return 0;
}
