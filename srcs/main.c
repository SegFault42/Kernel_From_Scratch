#include "../include/kernel.h"

char	*vidptr = (char *)VIDEO_MEM_BEGIN;

void	kmain(void)
{
	const char	*str = "Hellfdl;skdjflkjsd;lfkj;lsdkjaf;lkjdsa;lfjks;aldjf;lkjdsa;fljdsa;lkjf;lsadkf;lkj";

	clear_screen();
	ft_kputstr(str);
	ft_kputchar('a');
	ft_kputstr_color(str, RED);

	return ;
}
