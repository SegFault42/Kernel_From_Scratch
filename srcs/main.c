#include "../include/kernel.h"

char	*vidptr = (char *)VIDEO_MEM_BEGIN;


void	kmain(void);

void	kmain(void)
{
	kfs_clear_screen();
	kfs_putstr_color(splash, LIGHT_GREEN);
	idt_init();
	kb_init();

	return ;
}
