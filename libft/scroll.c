#include "libft.h"

// move cursor in x and y position
void	move_cursor(uint8_t x, uint8_t y)
{
	uint16_t pos = 0;
	char	*tmp = (char *)VIDEO_MEM_BEGIN;

	vidptr = (char *)VIDEO_MEM_BEGIN;
	pos = ((y * MAX_COLUMNS) * 2) + (x * 2);
	vidptr += pos;
}

void	simple_scroll(void)
{
	// scrolling
	kfs_kmemmove((char *)VIDEO_MEM_BEGIN,
				(char *)VIDEO_MEM_BEGIN + (MAX_COLUMNS * 2),
				(MAX_COLUMNS * 2) * (MAX_LINES - 1));

	// replace cursor
	vidptr = (char *)(VIDEO_MEM_END) - (MAX_COLUMNS * 2);
	/*move_cursor(0, 24);*/

	// memset to 0 last line
	kfs_kmemset(vidptr, 0, MAX_COLUMNS * 2);
	for (int i =0; i< 100000000; i++){}
}
