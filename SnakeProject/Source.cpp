#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "console.h"
#include <iostream>
#include <ctime>

enum State { UP, DOWN, LEFT, RIGHT };

struct Locate
{
	int x, y;
};

struct Snake
{
	Locate dot[200];
	int n;
	State state;
};

struct Fruit
{
	Locate f;
};

void Create(Snake &snake, Fruit &fruit)
{
	snake.n = 2;
	snake.dot[0].x = 47;
	snake.dot[0].y = 0;
	snake.dot[1].x = 46;
	snake.dot[1].y = 0;
	snake.state = RIGHT;

	fruit.f.x = 45 + rand() % 30;
	fruit.f.y = rand() % 30;
}


void Display(Snake snake, Fruit fruit)
{
	clrscr();
	//system("cls");

	for (int i = 44; i < 76; i++) {
		for (int j = 0; j < 30; j++) {
			if (i == 44 || i == 75) {
				gotoXY(i, j);
				putchar(219);
			}	
		}
	}

	gotoXY(fruit.f.x, fruit.f.y);
	putchar(254);

	for (int i = 0; i < snake.n; i++) {
		gotoXY(snake.dot[i].x, snake.dot[i].y);
		putchar(254);
	}
	
}

void Control(Snake &snake)
{
	for (int i = snake.n - 1; i > 0; i--) {
		snake.dot[i] = snake.dot[i - 1];
	}

	if (_kbhit())
	{
		int key = _getch();
		if (key == 'A' || key == 'a' && snake.state != RIGHT) {
			snake.state = LEFT;
		}
		else if (key == 'S' || key == 's' && snake.state != UP) {
			snake.state = DOWN;
		}
		else if (key == 'D' || key == 'd' && snake.state != LEFT) {
			snake.state = RIGHT;
		}
		else if (key == 'W' || key == 'w' && snake.state != DOWN) {
			snake.state = UP;
		}
	}

	if (snake.state == LEFT) {
		snake.dot[0].x--;
	}
	else if (snake.state == RIGHT) {
		snake.dot[0].x++;
	}
	else if (snake.state == UP) {
		snake.dot[0].y--;
	}
	else if (snake.state == DOWN) {
		snake.dot[0].y++;
	}
}

void Operate(Snake &snake, Fruit &fruit, int &score, int &dem, int &speed)
{
	if (fruit.f.x == snake.dot[0].x && fruit.f.y == snake.dot[0].y) {

		dem += 1;
		score += 5;

		if (dem == 5) {
			if (speed > 10) {
				speed -= 10;
			}
			dem = 0;
		}

		for (int i = snake.n; i > 0; i--) {
			snake.dot[i] = snake.dot[i - 1];
		}
		snake.n++;


		if (snake.state == LEFT) {
			snake.dot[0].x--;
		}
		else if (snake.state == RIGHT) {
			snake.dot[0].x++;
		}
		else if (snake.state == UP) {
			snake.dot[0].y--;
		}
		else if (snake.state == DOWN) {
			snake.dot[0].y++;
		}

		fruit.f.x = 45 + rand() % 30;
		fruit.f.y = rand() % 30;
	}
}

void Nocursortype() //an con tro
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

int main()
{
	//for (int i = 0; i <= 255; i++)
	//{
	//	printf("%d %c\n", i, i);
	//}

	//for (int i = 0; i <= 119; i++) {
	//	for (int j = 0; j <= 29; j++) {
	//		if (i == 0) {
	//			gotoXY(i, j);
	//			printf("%d", i);
	//		}
	//		else if (j == 0) {
	//			gotoXY(i, j);
	//			printf("%d", j);
	//		}
	//		
	//	}
	//}

	//while (1)
	//{
	//	if (_kbhit()) {
	//		int key = _getch();
	//		printf("%c", key);
	//	}
	//}

	srand(time(NULL));
	Nocursortype();
	Snake snake;
	Fruit fruit;
	Create(snake, fruit);
	int score = 0;
	int dem = 0;
	int speed = 50;
	while (1)
	{

		//hien thi
		Display(snake, fruit);

		//dieu khien
		Control(snake);

		//xu ly
		Operate(snake, fruit, score, dem, speed);

		//ket thuc
		/*gotoXY(77, 8);
		printf("x:%d y:%d", snake.dot[0].x, snake.dot[0].y);*/
		gotoXY(77, 8);
		printf("Diem: %d", score);
		gotoXY(77, 9);
		if (snake.dot[0].x < 45 || snake.dot[0].x > 74 || snake.dot[0].y < 0 || snake.dot[0].y > 29)
		{
			gotoXY(77, 10);
			printf("DAMN!! DUNG XE	");
			while (_getch() != 13);
			break;
		}
		else
		{
			for (int i = 1; i < snake.n; i++) {
				if (snake.dot[0].x == snake.dot[i].x && snake.dot[0].y == snake.dot[i].y)
				{
					gotoXY(77, 10);
					printf("THUA ROI");
					while (_getch() != 13);
					break;
				}
			}
		}
		Sleep(speed);
	}
	return 0;
}