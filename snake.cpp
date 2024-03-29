#define  _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <graphics.h>
#define SNAKE_MAX_NUM 500
#include <conio.h>
#include <stdlib.h>
//控制枚举
enum {
	UP,
	DOWN,
	LEFT,
	RIGHT,
};
// 蛇结构体
struct Snake
{
	int size;//蛇的节数
	int dir;//蛇的方向
	int speed;//蛇的速度
	POINT coor[SNAKE_MAX_NUM];//蛇的坐标
}snake;


//食物结构体
struct Food
{
	int r; //食物半径
	int x;	//食物x
	int y;	//食物y
	bool exist; //是否存在
}apple;
int source = 0;
//初始化图形化界面和蛇的位置
void GameInit() {
	initgraph(640, 480,SHOWCONSOLE);
	snake.size = 3;
	snake.dir=RIGHT;
	snake.speed = 10;
	for (int i = snake.size-1; i >= 0; i--)
	{
		snake.coor[i].x = 10*i+20;
		snake.coor[i].y = 10;
	}
	srand(GetTickCount());
}


void GameDraw() {
	//初始化 图形	
	setbkcolor(BLACK);
	cleardevice();
	for (int i = 0; i < snake.size;i++) {
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	if (apple.exist) {
		solidcircle(apple.x, apple.y, apple.r);
	}
}
void S_move() {
	for (int i = snake.size-1; i > 0; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
		printf("i=%d x=%d y=%d\n",i,snake.coor[i].x,snake.coor[i].y);
	}
	switch (snake.dir)
	{
	case UP:
		snake.coor[0].y-= snake.speed;
		if (snake.coor[0].y == 0)
		{
			snake.coor[0].y = 480;
		}
		break;
	case DOWN:
		snake.coor[0].y+= snake.speed;
		if (snake.coor[0].y == 480)
		{
			snake.coor[0].y = 0;
		}
		break;
	case RIGHT:
		snake.coor[0].x+= snake.speed;
		if (snake.coor[0].x == 640)
		{
			snake.coor[0].x = 0;
		}
		break;
	case LEFT:
		snake.coor[0].x-= snake.speed;
		if (snake.coor[0].x == 0)
		{
			snake.coor[0].x = 640;
		}
		break;
	}
}
void Keycontral() {
	if (_kbhit())
	{
		switch (_getch())
		{
			//上下左右
		case 'w':
		case 'W':
		case '72':
			if (snake.dir != DOWN)
			{
				snake.dir = UP;
				break;
			}
		case 's':
		case 'S':
		case '80':
			if (snake.dir != UP)
			{
				snake.dir = DOWN;
				break;
			}
		case 'a':
		case 'A':
		case '75':
			if (snake.dir !=RIGHT)
			{
				snake.dir = LEFT;
				break;
			}
		case 'd':
		case 'D':
		case '77':
			if (snake.dir != LEFT)
			{
				snake.dir = RIGHT;
				break;
			}
		}
	}
	
}

//吃苹果
void EatFood() {
	if ((snake.coor[0].x>=apple.x-apple.r&&snake.coor[0].x<=apple.x+apple.r)&&(snake.coor[0].y >= apple.y - apple.r && snake.coor[0].y <= apple.y + apple.r))
	{
		snake.size++;
		apple.exist = FALSE;
	}
}

// 生成苹果
void HappenApple() {
	if (apple.exist==FALSE)
	{
		apple.x = rand() % 630;
		apple.y = rand() % 470;
		apple.r = 7;
		apple.exist = TRUE;
	}
}


int main() {
	GameInit();
	while (true)
	{
		GameDraw();
		S_move();
		HappenApple();
		Keycontral();
		EatFood();
		Sleep(200);
	}
	return 0;
}