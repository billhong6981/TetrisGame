#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#define TTY_PATH "/dev/tty"
#define STTY_ON "stty raw -echo -F"
#define STTY_OFF "stty -raw echo -F"
/**
 * struct block - data structure for the block
 * @x:
 * @y:
 * @blockType:
 * blockDirection:
 */
typedef struct block
{
	int x;
	int y;
	int blockType;
	int blockDirect;
} Block;
Block bl;
int map[21][14];
char direct;
int node[7][4][16] = {
	{{0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0}, /* Bar Shape */
	 {0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0},
	 {0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0},
	 {0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0}},
	{{1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0}, /* Square Shape */
	 {1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
	 {1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
	 {1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0}},
	{{0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0}, /* T Shape */
	 {0,1,0,0,0,1,1,0,0,1,0,0,0,0,0,0},
	 {0,0,0,0,1,1,1,0,0,1,0,0,0,0,0,0},
	 {0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0}},
	{{0,1,1,0,0,1,0,0,0,1,0,0,0,0,0,0}, /* Mirrored L Shape */
	 {0,0,0,0,1,1,1,0,0,0,1,0,0,0,0,0},
	 {0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0},
	 {1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0}},
	{{1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0}, /* L Shape */
	 {0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0},
	 {0,1,0,0,0,1,0,0,0,1,1,0,0,0,0,0},
	 {0,0,0,0,1,1,1,0,1,0,0,0,0,0,0,0}},
	{{0,1,0,0,0,1,1,0,0,0,1,0,0,0,0,0}, /* Mirrored Z Shape */
	 {0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0},
	 {0,1,0,0,0,1,1,0,0,0,1,0,0,0,0,0},
	 {0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0}},
	{{0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0}, /* Z Shape */
	 {1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
	 {0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0},
	 {1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0}}
};

/**
 * init_map - the function initializes the frame
 * @: input void
 * Return: void
 */
void init_map(void)
{
	int i, j;

	for (i = 0; i < 21; i++)
	{
		for (j = 0; j < 14; j++)
		{
			if (j == 0 || j == 13)
				map[i][j] = 200;
			else if (i == 20)
				map[i][j] = 201;
			else
				map[i][j] = 0;
		}
	}
}

/**
 * new_block - a function genarates a randome block shape
 * @: void
 * Return: void
 */
void new_block(void)
{
	int blockType = rand() % 7;
	int blockDirect = rand() % 4;
	int x = 1;
	int y = 5;

	bl.x = x;
	bl.y = y;
	bl.blockType = blockType;
	bl.blockDirect = blockDirect;
}

/**
 * input - a function loads the block to the frame
 */
void input(void)
{
	int i, j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (node[bl.blockType][bl.blockDirect][i * 4 + j] == 1)
				map[bl.x + i][bl.y + j] = 1;
		}
	}
}

/**
 * output - a function clear the data after the block moving
 */
void output(void)
{
	int i, j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
			if (node[bl.blockType][bl.blockDirect][i * 4 + j] == 1)
				map[bl.x + i][bl.y + j] = 0;
	}
}

/**
 * change - a function set the data to 10 after block moving completly
 */
void change(void)
{
	int i, j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (node[bl.blockType][bl.blockDirect][i * 4 + j] == 1)
				map[bl.x + i][bl.y + j] = 10;
		}
	}
	for (j = 1; j < 13; j++)
	{
		if (map[5][j] == 10)
		{
			system("clear");
			printf("Game Over !!!!!\n");
			exit(1);
		}
	}
}

/**
 * print_map - a function prints current status
 */
void print_map(void)
{
	int i, j;

	for (i = 5; i < 21; i++)
	{
		for (j = 0; j < 14; j++)
		{
			if (map[i][j] == 200)
				printf("#");
			else if (map[i][j] == 201)
				printf(" # ");
			else if (map[i][j] == 0)
				printf("   ");
			else if (map[i][j] == 1)
				printf(" * ");
			else if (map[i][j] == 10)
				printf(" @ ");
		}
		printf("\n");
	}
}

/**
 * delLine - a function deletes line if filled it
 * @n: the deepest line number still possible to be filled
 */
void delLine(int n)
{
	int i, j;

	for (j = 1; j < 13; j++)
		map[n][j] = 0;
	for (i = n; i > 5; i--)
	{
		for (j = 1; j < 13; j++)
		{
			if (map[i - 1][j] != 1)
				map[i][j] = map[i - 1][j];
		}
	}
}

/**
 * isFillLine - checks the line whether be filled or not
 */
void isFillLine(void)
{
	int i, j;
	int fals;

	for (i = 19; i > 5; i--)
	{
		fals = 1;
		for (j = 1; j < 13; j++)
		{
			if (map[i][j] != 10)
			{
				fals = 0;
				continue;
			}
		}
		if (fals)
			delLine(i);
	}
}

/**
 * down - the block moves down
 */
void down(void)
{
	int i, j;
	int fale = 1;

	for (i = 3; i >= 0; i--)
	{
		for (j = 0; j < 4; j++)
		{
			if (node[bl.blockType][bl.blockDirect][i * 4 + j] == 1)
			{
				if (map[bl.x + i + 1][bl.y + j] == 10 || map[bl.x + i + 1][bl.y + j] == 201)
				{
					change();
					fale = 0;
					new_block();
					isFillLine();
					return;
				}
			}
		}
	}
	if (fale)
	{
		output();
		bl.x += 1;
		input();
	}
}

/**
 * right - the block moves to right when press 'd'
 */
void right(void)
{
	int i, j;
	int fale = 1;

	for (i = 3; i >= 0; i--)
	{
		for (j = 0; j < 4; j++)
		{
			if (node[bl.blockType][bl.blockDirect][i * 4 + j] == 1)
			{
				if (map[bl.x + i][bl.y + j + 1] == 10 || map[bl.x + i][bl.y + j + 1] == 200)
				{
					fale = 0;
					return;
				}
			}
		}
	}
	if (fale)
	{
		output();
		bl.y += 1;
		input();
	}
}

/**
 * left - the block moves to left when press 'a'
 */
void left(void)
{
	int i, j;
	int fale = 1;

	for (i = 3; i >= 0; i--)
	{
		for (j = 0; j < 4; j++)
		{
			if (node[bl.blockType][bl.blockDirect][i * 4 + j] == 1)
			{
				if (map[bl.x + i][bl.y + j - 1] == 10 || map[bl.x + i][bl.y + j - 1] == 200)
				{
					fale = 0;
					return;
				}
			}
		}
	}
	if (fale)
	{
		output();
		bl.y -= 1;
		input();
	}
}

/**
 * change_block - the block rotates when press ' '
 */
void change_block(void)
{
	int i, j;
	int fals = 1;

	output();
	bl.blockDirect += 1;
	bl.blockDirect %= 4;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (node[bl.blockType][bl.blockDirect][i * 4 + j] == 1)
			{
				if (map[bl.x + i][bl.y + j] != 0)
				{
					fals = 0;
					break;
				}
			}
		}
	}
	if (fals)
	{
		input();
	}
	else
	{
		bl.blockDirect -= 1;
		input();
	}
}

/**
 * in_direct - input command to change block direction
 */
char in_direct(void)
{
	fd_set fd;
	struct timeval tv;
	char ch;

	FD_ZERO(&fd);
	FD_SET(0, &fd);
	tv.tv_sec = 0;
	tv.tv_usec = 10;
	if (select(1, &fd, NULL, NULL, &tv) > 0)
	{
		ch = getchar();
	}
	return (ch);
}

/**
 * main - the game entry point
 * @: input void
 *
 * Return: 0 on success, otherwise if failure
 */
int main(void)
{
	char ch;
	int num = 0;

	srand(time(NULL));
	init_map();
	new_block();
	input();
	while(1)
	{
		usleep(500000);
		system(STTY_ON TTY_PATH);
		ch = in_direct();
		system("clear");
		if(ch == 'a' && num <= 1)
		{
			left();
			print_map();
			num++;
			continue;
		}
		else if (ch == 'd' && num <= 1)
		{
			right();
			print_map();
			num++;
			continue;
		}
		else if (ch == ' ' && num <= 1)
		{
			change_block();
			print_map();
			num++;
			continue;
		}
		else if (ch == 'q')
		{
			system("clear");
			printf("Game Over!!!!\n");
			exit(0);
		}
		down();
		print_map();
		num = 0;
	}
	return (0);
}
