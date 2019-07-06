#include "tetris.h"
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
