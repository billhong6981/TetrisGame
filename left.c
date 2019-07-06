#include "tetris.h"
/**
 *
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
