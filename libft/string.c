#include "libft.h"

void	ft_kputchar(int c)
{
	if (vidptr == (char *)VIDEO_MEM_END) {
		simple_scroll();
	}
	*vidptr++ = c;
	*vidptr++ = LIGHT_GREY;
}

void	ft_kputstr(const char *str)
{
	ft_kputstr_color(str, LIGHT_GREY);
}

void	ft_kputstr_color(const char *str, uint8_t color)
{
	while (*str) {
		if (vidptr == (char *)VIDEO_MEM_END) {
			simple_scroll();
		}
		*vidptr++ = *str;
		*vidptr++ = color;

		++str;
	}
}
