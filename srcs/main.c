#include "../include/kernel.h"

char	*vidptr = (char *)VIDEO_MEM_BEGIN;

/*void	kmain(t_multiboot multiboot);*/

int	kmain(t_multiboot multiboot)
{
	init_gdt();
	kfs_clear_screen();

	for (int i = 0; i < 967; i++) {
		kfs_putchar_color(splash[i], LIGHT_GREEN);
		for (int j = 0; j < 400000; j++) {} // fake sleep
	}

	while (1)
		keyboard();

	return (0);
}
