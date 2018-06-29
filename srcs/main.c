#include "../include/kernel.h"

char	*vidptr = (char *)VIDEO_MEM_BEGIN;

void	kmain(void);

void	kmain(void)
{
	kfs_clear_screen();
	kfs_kputstr("Hello, je suis un ordinateur.\nJ'ai ete code par SegFault42.\n:)");
	return ;
}
