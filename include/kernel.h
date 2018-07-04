#ifndef KERNEL_H
#define KERNEL_H

#include "../libft/include/libft.h"
#include "../include/keyboard.h"
#include "../include/splash.h"

typedef struct	workspace
{
	char		*ptr;
	char		buff_video[(MAX_COLUMNS * MAX_LINES) * 2];
}				workspace;

void	clear_screen(void);
void	write_to_pos(uint8_t x, uint8_t y, const char *str);
void	switch_workspace(int keycode);

#endif
