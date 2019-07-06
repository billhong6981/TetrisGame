#include "tetris.h"
/**
 *
 */
void change_block(void)
{
	int i, j;
	output();
	int fals = 1;
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
