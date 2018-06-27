#include "libft.h"

void	ft_kputstr(const char *str)
{
	while (*str) {
		if (vidptr == (char *)VIDEO_MEM_END) {
			// scrolling
			ft_kmemmove((char *)VIDEO_MEM_BEGIN,
 						(char *)VIDEO_MEM_BEGIN + (MAX_COLUMNS * 2),
						(MAX_COLUMNS * 2) * (MAX_LINES - 1));
			// replace cursor
			vidptr = (char *)(VIDEO_MEM_END) - (MAX_COLUMNS * 2);
			// memset to 0 last line
			ft_kmemset(vidptr, 0, MAX_COLUMNS * 2);
		}
		*vidptr++ = *str;
		*vidptr++ = GREEN;

		++str;
		for (int i = 0; i < 100000; i++) {}
	}
}

