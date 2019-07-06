#include "tetris.h"
/**
 *
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
				printf(" ");
			else if (map[i][j] == 1)
				printf(" * ");
			else if (map[i][j] == 10)
				printf(" @ ");
		}
		printf("\n");
	}
}
