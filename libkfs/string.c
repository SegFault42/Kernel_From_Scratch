#include "libkfs.h"

static char	*skip_blank(char *str)
{
	while (*str == ' ' || *str == '\n')
		str++;

	return (str);
}

void kfs_remove_extra_white_space(char *str)
{
	char	*str_ptr = str; // save str address
	char	array[kfs_strlen(str) + 1]; // alloc space to write formatted str
	char	*ptr = array; // ptr to manipule array;

	memset(array, 0, kfs_strlen(str) + 1);

	// Remove white space in begining string
	str = skip_blank(str);

	while (*str) {
		// copy one space before skipping all spaces
		if (*str == ' ') {
			*ptr = ' ';
			++ptr;
		}

		// skip all space
		str = skip_blank(str);

		// Copy *str in *ptr
		*ptr = *str;

		// incr
		str++;
		ptr++;
	}

	// erase str with the new formatted string
	kfs_strcpy(str_ptr, array);
}

static void	print_offset(void *addr)
{
	// Print offset and padding
	kfs_putstr(to_hex_32((uint32_t)addr));
	kfs_putstr("  ");
}

static void	print_hex_value(void *addr)
{
	// print hex value and padding
	for (int i = 0; i < 16; i++) {
		kfs_putstr(to_hex_8(*(uint8_t *)addr));

		if (i == 7)
 			kfs_putstr("  ");
		else
			kfs_putstr(" ");

		addr++;
	}

	kfs_putstr(" |");
}

static void	print_ascii_value(void *addr)
{
	// Print value in ascii
	for (int i = 0; i < 16; i++) {
		if (isprint(*(uint8_t *)addr))
			kfs_putchar(*(uint8_t *)addr);
		else
			kfs_putchar('.');

		addr++;
	}

	kfs_putchar('\n');
}

void	hexdump(void *addr)
{
	print_offset(addr);
	print_hex_value(addr);
	print_ascii_value(addr);
}

char	*to_hex_16(uint16_t key)
{
	char	*value = "0000";

	kfs_strcpy(&value[0], to_hex_8((key >> 8) & 0xFF));
	kfs_strcpy(&value[2], to_hex_8(key & 0xFF));

	return (value);
}

char	*to_hex_32(uint32_t key)
{
	char	*value = "00000000";

	kfs_strcpy(&value[0], to_hex_8((key >> 24) & 0xFF));
	kfs_strcpy(&value[2], to_hex_8((key >> 16) & 0xFF));
	kfs_strcpy(&value[4], to_hex_8((key >> 8) & 0xFF));
	kfs_strcpy(&value[6], to_hex_8(key & 0xFF));

	return (value);
}

char	*to_hex_8(uint8_t key)
{
    char	*value = "00";
    char	*hex = "0123456789ABCDEF";

    value[0] = hex[(key >> 4) & 0xF];
    value[1] = hex[key & 0xF];

	return (value);
}

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
