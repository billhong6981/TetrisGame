#ifndef _TETRIS_H
#define _TETRIS_H
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#define TTY_PATH "/dev/tty"
#define STTY_ON "stty -raw -echo -F"
#define STTY_OFF "stty -raw echo -F"
#include "tetris.h"
/**
 * struct block - data structure for the block
 * @x:
 * @y:
 * @blockType:
 * blockDirection:
 */
extern struct block
{
	int x;
	int y;
	int blockType;
	int blockDirect;
} bl;

extern int map[21][14];
extern char direct;
extern int node[7][4][16];

/* The following are prototypes */
void init_map(void);
void new_block(void);
void input(void);
void output(void);
void change(void);
void print_map(void);
void delLine(int n);
void isFillLine(void);
void down(void);
void right(void);
void left(void);
void change_block(void);
char in_direct(void);

#endif
