#include "../include/kernel.h"

#define ONE_SECOND 170000000

static void	kfs_sleep(int second)
{
	for (int i = 0; i < second * ONE_SECOND; i ++) {
		asm("nop");
	}
}

static void count_nb_elem(char *str, char c)
{
	int	nb_elem = 0;

	while (*str) {
		if (*str == c)
			nb_elem++;
		str++;
	}
}

static void	strsplit(char *cmd, char split[3][128], char c, int nb_elem)
{
	int	i = 0;
	int	j = 0;

	count_nb_elem(cmd, c);

	// loop to reach '\0'
	while (*cmd) {
		// if character is not c, we store c in our buffer
		if (*cmd != c) {
			split[i][j] = *cmd;
		// else we put a '\0' in end of string
		} else {
			split[i][j] = '\0';
			i++;
			j = -1;
		}
		// incr to next array
		j++;
		cmd++;
	}
}

static void	hexdump_cmd(char *cmd)
{
	void	*tmp = 0x0;


	for (int i = 0; i < 0xfff; i++) {
		hexdump(tmp);
		tmp += 16;
		for (int i = 0; i < 1000000; i++) {} // fake sleep
	}
}

void	shell(void)
{
	char	cmd[128] = {0};
	char	split[3][128] = {0};

	get_input(cmd);

	strsplit(cmd, split, ' ');

	if (!(kfs_strcmp(cmd, "hexdump\n"))) {
		hexdump_cmd(cmd);
	}
	/*else if (!(kfs_strcmp(cmd, "reboot\n"))) {*/
		/*reboot();*/
	/*}*/
}

