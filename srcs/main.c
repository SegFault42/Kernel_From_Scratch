#include "../include/kernel.h"

char	*vidptr = (char *)VIDEO_MEM_BEGIN;

void	kmain(void)
{
	const char	*str = "Bonjour";

	kfs_clear_screen();
	kfs_kputstr("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
	kfs_kputchar('a');
	return ;
}
