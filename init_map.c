#include "tetris.h"
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
