#include "tetris.h"
/**
 *
 */
char in_direct(void)
{
	fd_set fd;
	struct timeval tv;
	char ch;
	FD_ZERO(&fd);
	FD_SET(0, &fd);
	tv.tv_sec = 0;
	tv.tv_usec = 10;
	if (select(1, &fd, NULL, NULL, &tv) > 0)
	{
		ch = getchar();
	}
	return (ch);
}
