#include "tetris.h"
/**
 *
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
