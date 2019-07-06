#include "tetris.h"
/**
 *
 */
void delLine(int n)
{
	int i, j;
	for (j = 1; j < 13; j++)
		map[n][j] = 0;
	for (i = n; i < 5; i--)
	{
		for (j = 1; j < 13; j++)
		{
			if (map[i - 1][j] != 1)
				map[i][j] = map[i - 1][j];
		}
	}
}
