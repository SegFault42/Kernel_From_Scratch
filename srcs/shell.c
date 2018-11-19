#include "../include/kernel.h"

#define ONE_SECOND 170000000

static void	kfs_sleep(int second)
{
	for (int i = 0; i < second * ONE_SECOND; i ++) {
		asm("nop");
	}
}

static int count_nb_elem(char *str, char c)
{
	int	nb_elem = 1;

	while (*str) {
		if (*str == c)
			nb_elem++;
		str++;
	}

	return (nb_elem);
}

static void	strsplit(char *cmd, char split[3][128], char c)
{
	int	i = 0;
	int	j = 0;

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

static void	hexdump_cmd(char *begin, char *end)
{
	void	*tmp = 0x0;


	for (int i = 0; i < 0xfff; i++) {
		hexdump(tmp);
		tmp += 16;
		kfs_sleep(1);
	}
}

void	shell(void)
{
	char	cmd[128] = {0};
	char	split[3][128] = {0};

	get_input(cmd);

	kfs_remove_extra_white_space(cmd);
	strsplit(cmd, split, ' ');

	kfs_putstr(split[0]);
	if (!(kfs_strcmp(split[0], "hexdump"))) {
		if (count_nb_elem(cmd, ' ') != 3)
			kfs_putstr("Usage : hexdump [addr begin] [addr end]\n");
		else
			hexdump_cmd(split[1], split[2]);
	}
	/*else if (!(kfs_strcmp(cmd, "reboot\n"))) {*/
		/*reboot();*/
	/*}*/
}

