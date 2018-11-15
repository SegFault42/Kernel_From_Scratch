#include "../include/kernel.h"

void	shell(void)
{
	char	cmd[128];
	char	*tmp = 0x0;

	kfs_memset(&cmd, 0, sizeof(cmd));

	get_input(cmd);

	if (!(kfs_strcmp(cmd, "hexdump\n"))) {
		for (int i = 0; i < 0xfff; i++) {
			hexdump(tmp);
			tmp += 16;
			for (int i = 0; i < 1000000; i++) {} // fake sleep
		}
	}
	/*else if (!(kfs_strcmp(cmd, "reboot\n"))) {*/
		/*reboot();*/
	/*}*/
}

