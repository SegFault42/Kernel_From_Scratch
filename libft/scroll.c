#include "libft.h"

void	simple_scroll()
{
	// scrolling
	kfs_kmemmove((char *)VIDEO_MEM_BEGIN,
				(char *)VIDEO_MEM_BEGIN + (MAX_COLUMNS * 2),
				(MAX_COLUMNS * 2) * (MAX_LINES - 1));

	// replace cursor
	vidptr = (char *)(VIDEO_MEM_END) - (MAX_COLUMNS * 2);

	// memset to 0 last line
	kfs_kmemset(vidptr, 0, MAX_COLUMNS * 2);
}
