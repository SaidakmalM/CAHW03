#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <math.h>

#define MAX_X 15
#define MAX_Y 15
#define MAX_FOOD_SIZE 1

typedef struct tail_t{
	int x;
	int y;
	} tail_t;
	
typedef struct snake_t{
	int x;
	int y;
	int direction;
	struct tail_t * tail;
	size_t tsize;
	}  snake_t;
	
typedef struct food 
	{
		int x;
		int y;
		time_t put_time;
		char point;
		int enable;
	} food[MAX_FOOD_SIZE];

// --> x
// || Y
// \/
// @**
struct snake_t initSnake(int x, int y, size_t tsize, int direction){
	struct snake_t snake;
	snake.x = x;
	snake.y = y;
	snake.direction = direction;
	snake.tsize = tsize;
	snake.tail = (tail_t *) malloc (sizeof(tail_t) * 100);
	for (int i =0; i < tsize; ++i){
		snake.tail[i].x = x + i +1;
		snake.tail[i].y = y;
		}
	return snake;
}

	
// @**
void printSnake(struct snake_t snake){
		char matrix[MAX_X][MAX_Y];
		for (int i = 0; i < MAX_X; ++i){
			for (int j = 0; j < MAX_Y; ++j)
			{
				matrix[i][j] = ' ';
				}}
		
		matrix[snake.x][snake.y] = '@';
		for (int i = 0; i < snake.tsize; ++i){
			matrix[snake.tail[i].x][snake.tail[i].y] = '*';
			}
		
		for (int j = 0; j < MAX_Y; ++j){
			for (int i = 0; i < MAX_X; ++i)
			{
				printf("%c", matrix[i][j]);
				}
				printf("\n");
				}
	}
	
// <--  @** tsize = 2
//     @**

//  @**      @***
//    * <--     *
//  ***        **
snake_t moveLeft(snake_t snake){
	for (int i = snake.tsize - 1; i > 0; i--){
		snake.tail[i] = snake.tail[i-1];
		}
	snake.tail[0].x = snake.x;
	snake.tail[0].y = snake.y;
	
	snake.x = snake.x - 1;
	if (snake.x < 0){
		snake.x = MAX_X - 1;
		}
	return snake;
	}	

snake_t moveUp(snake_t snake){
	for (int i = snake.tsize - 1; i > 0; i--){
		snake.tail[i] = snake.tail[i-1];
		}
	snake.tail[0].x = snake.x;
	snake.tail[0].y = snake.y;
	
	snake.y = snake.y - 1;	
	if (snake.y < 0){
		snake.y = MAX_Y - 1;
		}
	return snake;
	}

snake_t moveRight(snake_t snake){
	for (int i = snake.tsize - 1; i > 0; i--){
		snake.tail[i] = snake.tail[i-1];
		}
	snake.tail[0].x = snake.x;
	snake.tail[0].y = snake.y;
	
	snake.x = snake.x + 1;	
	if (snake.x > MAX_X){
		snake.x = 0;
		}
	return snake;
	}	

snake_t moveDown(snake_t snake){
	for (int i = snake.tsize - 1; i > 0; i--){
		snake.tail[i] = snake.tail[i-1];
		}
	snake.tail[0].x = snake.x;
	snake.tail[0].y = snake.y;
	
	snake.y = snake.y + 1;	
	if (snake.y > MAX_Y){
		snake.y = 0;
		}
	return snake;
	}	

int check_direction (snake_t snake, int direction)
	{
		int differ = fabs(snake.direction - direction);
		if (differ == 2) return 0;
		else return 1;
	}

snake_t key_pressed_action(snake_t snake, int direction)
	{
		if (check_direction(snake, direction) == 1)
			{
				switch (direction)
					{
						case 1:{
							snake = moveLeft(snake);
							sleep(1);
							system("cls");
							printSnake(snake);
						}
						case 2:{
							snake = moveUp(snake);
							sleep(1);
							system("cls");
							printSnake(snake);
						}
						case 3:{
							snake = moveRight(snake);
							sleep(1);
							system("cls");
							printSnake(snake);
						}
						case 4:{
							snake = moveDown(snake);
							sleep(1);
							system("cls");
							printSnake(snake);
						}
					}
			}
			snake.direction = direction;
		return(snake);
	}
	
int main(){
	struct snake_t snake = initSnake( 10, 5, 2, 1);
	printSnake(snake);
	int key_pressed = 0;
	int direction = 0; //1-Left(a,A),2-Up(w,W),3-Right(d,D),4-Down(s,S) 
	while ((key_pressed != 81) & (key_pressed != 113) & (key_pressed != 27))
	// "q", "Q", "Esc" - exit or quit
		{
			key_pressed = getch();
			switch (key_pressed)
				{
					case 97: direction = 1; // "a"
					break;
					case 65: direction = 1; // "A"
					break;
					case 100: direction = 3; // "d"
					break;
					case 68: direction = 3; // "D"
					break;
					case 113: direction = 2; // "w"
					break;
					case 87: direction = 2; // "W"
					break;
					case 115: direction = 4; // "s"
					break;
					case 83: direction = 4; // "S"
					break;
				}
			snake = key_pressed_action(snake, direction);
		}
	return 0;
	}
