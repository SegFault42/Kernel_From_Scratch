#include "../include/kernel.h"

char	*vidptr = (char *)VIDEO_MEM_BEGIN;


void	kmain(void);

void	kmain(void)
{
	kfs_clear_screen();
	for (int i = 0; splash[i]; i++) {
		kfs_putchar_color(splash[i], LIGHT_GREEN);
		for (int j = 0; j < 400000; j++) {}
	}
	idt_init();
	kb_init();

	return ;
}
