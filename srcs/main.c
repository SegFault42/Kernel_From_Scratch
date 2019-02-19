#include "../include/kernel.h"

char	*vidptr = (char *)VIDEO_MEM_BEGIN;

/*void	kmain(t_multiboot multiboot);*/

int	kmain(__attribute__((unused)) t_multiboot multiboot)
{
	init_gdt();
	kfs_clear_screen();
	display_splash_screen();

	// Print prompt
	kfs_putstr_color("$> ", GREEN);

	// exec shell and reprint prompt
	while (1) {
		shell();
		kfs_putstr_color("$> ", GREEN);
	}

	return (0);
}
