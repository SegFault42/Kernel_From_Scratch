#ifndef LIBFT_H
#define LIBFT_H

#define VIDEO_MEM_BEGIN	0xb8000
#define VIDEO_MEM_END	0xb8FA0
#define MAX_LINES		25
#define MAX_COLUMNS		80
#define CURSOR_Y ((vidptr - (char *)VIDEO_MEM_BEGIN) / 2) / MAX_COLUMNS

#define BLACK			0x00
#define BLUE			0x01
#define GREEN			0x02
#define CYAN			0x03
#define RED				0x04
#define MAGENTA			0x05
#define BROWN			0x06
#define LIGHT_GREY		0x07
#define DARK_GREY		0x08
#define LIGHT_BLUE		0x09
#define LIGHT_GREEN		0x0a
#define LIGHT_CYAN		0x0b
#define LIGHT_RED		0x0c
#define LIGHT_MAGENTA	0x0d
#define LIGHT_BROWN		0x0e
#define WHITE			0x0f

typedef char	uint8_t;
typedef short	uint16_t;
typedef int		uint32_t;
typedef long	uint64_t;
typedef long	size_t;

extern char		*vidptr;

// string.c
void	kfs_putstr(const char *str);
void	kfs_putstr_color(const char *str, uint8_t color);
void	kfs_putchar(int c);
void	kfs_putnbr(int c);
void	kfs_putchar_color(int c, uint8_t color);

// scroll.c
void	simple_scroll(void);
void	move_cursor(uint16_t x, uint16_t y);
void	kfs_clear_screen(void);

// memory.c
void	*kfs_memmove(void *dest, const void *src, size_t n);
void	*kfs_memset(void *b, int c, size_t len);

#endif
