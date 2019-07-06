#include "tetris.h"
/**
 *
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
