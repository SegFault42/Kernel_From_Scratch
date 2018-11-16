#include "../include/kernel.h"

#define ONE_SECOND 170000000

static void	kfs_sleep(int second)
{
	for (int i = 0; i < second * ONE_SECOND; i ++) {
		asm("nop");
	}
}

static void	strsplit(char *cmd, char split[3][128], char c)
{
	int	i = 0;
	int	j = 0;

	while (*cmd) {
		if (*cmd != c) {
			split[i][j] = *cmd;
		} else {
			split[i][j] = '\0';
			i++;
			j = -1;
		}
		j++;
		cmd++;
	}

	for (int i = 0; i < 3 * 128; i++) {
		hexdump(split);
		kfs_sleep(1);
	}
	kfs_putstr(split[0]);
	kfs_putstr(split[1]);
	kfs_putstr(split[2]);
}

static void	hexdump_cmd(char *cmd)
{
	void	*tmp = 0x0;


	/*for (int i = 0; i < 0xfff; i++) {*/
		/*hexdump(tmp);*/
		/*tmp += 16;*/
		/*for (int i = 0; i < 1000000; i++) {} // fake sleep*/
	/*}*/
}

void	shell(void)
{
	char	cmd[128];
	char	split[3][128];

	kfs_memset(&cmd, 0, sizeof(cmd));

	get_input(cmd);

	strsplit(cmd, split, ' ');

	if (!(kfs_strcmp(cmd, "hexdump\n"))) {
		hexdump_cmd(cmd);
	}
	/*else if (!(kfs_strcmp(cmd, "reboot\n"))) {*/
		/*reboot();*/
	/*}*/
}

