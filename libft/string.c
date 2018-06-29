#include "libft.h"

void kfs_putnbr(int n)
{
	if (n == -2147483648)
	{
		kfs_kputstr("-2");
		n = 147483648;
	}
	if (n < 0)
	{
		kfs_kputchar('-');
		n = -n;
	}
	if (n > 9)
	{
		kfs_putnbr(n / 10);
		kfs_putnbr(n % 10);
	}
	else
		kfs_kputchar('0' + n);
}

void	kfs_kputchar_color(int c, uint8_t color)
{
	// scroll line if cursor is at last x position
	if (vidptr == (char *)VIDEO_MEM_END)
		simple_scroll();

	if (c == '\n') {
		// clear cursor
		*(vidptr + 1) = 0;
		move_cursor(0, (uint16_t)CURSOR_Y + 1);
	} else {
		*vidptr++ = (char)c;
		*vidptr++ = color;
		// put cursor in grey light;
		*(vidptr + 1) |= (1 << 4) | (1 << 5) | (1 << 6);
	}
}

void	kfs_kputchar(int c)
{
	kfs_kputchar_color(c, LIGHT_GREY);
}

void	kfs_kputstr(const char *str)
{
	kfs_kputstr_color(str, LIGHT_GREY);
}

void	kfs_kputstr_color(const char *str, uint8_t color)
{
	while (*str) {
		kfs_kputchar_color(*str, color);
		++str;
	}
}

void	kfs_clear_screen(void)
{
	uint16_t	i = 0;

	vidptr = (char *)VIDEO_MEM_BEGIN;
	while (i < (MAX_COLUMNS * MAX_LINES) * 2) {
		vidptr[i] = ' ';
		vidptr[i+1]= BLACK;
		i += 2;
	}
}
