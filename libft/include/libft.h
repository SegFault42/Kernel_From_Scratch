#ifndef LIBFT_H
#define LIBFT_H

#define VIDEO_MEM_BEGIN	0xb8000
#define VIDEO_MEM_END	0xb8FA0
#define MAX_LINES		25
#define MAX_COLUMNS		80

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

char	*vidptr;

void	ft_kputstr(const char *str);
//void	clear_screen(void);
//void	write_to_pos(uint8_t x, uint8_t y, const char *str);
void	*ft_kmemmove(void *dest, const void *src, size_t n);
void	*ft_kmemset(void *b, int c, size_t len);

#endif
