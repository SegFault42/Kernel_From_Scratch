#include "libkfs.h"

char	*kfs_strcpy(char *dst, const char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	kfs_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s2[i] != s1[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

void kfs_putnbr(int n)
{
	if (n == -2147483648)
	{
		kfs_putstr("-2");
		n = 147483648;
	}
	if (n < 0)
	{
		kfs_putchar('-');
		n = -n;
	}
	if (n > 9)
	{
		kfs_putnbr(n / 10);
		kfs_putnbr(n % 10);
	}
	else
		kfs_putchar('0' + n);
}

void	kfs_putchar_color(int c, uint8_t color)
{
	if (c == '\n') {
		// clear cursor
		*(vidptr + 1) = 0;
		move_cursor(0, (uint16_t)CURSOR_Y + 1);
	} else if (c == '\b') {
		if (vidptr != (char *)VIDEO_MEM_BEGIN) {
			*vidptr = 0x00;
			*(vidptr + 1) = 0x00;
			vidptr -= 2;
		}
		while (*vidptr == 0x0) {
			if (vidptr != (char *)VIDEO_MEM_BEGIN) {
				*vidptr = 0x00;
				*(vidptr + 1) = 0x00;
				vidptr -= 2;
			}
		}
	} else {
		*vidptr++ = (char)c;
		*vidptr++ = color;
	}
	// scroll line if cursor is at last x position
	if (vidptr == (char *)VIDEO_MEM_END)
		simple_scroll();

	// put cursor in grey light;
	*vidptr = 0x0;
	*(vidptr + 1) |= (1 << 4) | (1 << 5) | (1 << 6);

}

size_t	kfs_strlen(const char *str)
{
	size_t	i = 0;
	while (*str) {
		str++;
		i++;
	}
	return (i);
}

void	kfs_putchar(int c)
{
	kfs_putchar_color(c, LIGHT_GREY);
}

void	kfs_putstr(const char *str)
{
	kfs_putstr_color(str, LIGHT_GREY);
}

void	kfs_putstr_color(const char *str, uint8_t color)
{
	while (*str) {
		kfs_putchar_color(*str, color);
		++str;
	}
}

void	kfs_clear_screen(void)
{
	uint16_t	i = 0;

	vidptr = (char *)VIDEO_MEM_BEGIN;
	while (i < (MAX_COLUMNS * MAX_LINES) * 2) {
		vidptr[i] = 0x0;
		vidptr[i+1]= 0x0;
		i += 2;
	}
}
