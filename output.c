#include "tetris.h"
/**
 *
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
