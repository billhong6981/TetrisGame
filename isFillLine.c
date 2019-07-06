#include "tetris.h"
/**
 *
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
