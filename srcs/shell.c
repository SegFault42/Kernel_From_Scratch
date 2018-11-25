#include "../include/kernel.h"

#define ONE_SECOND 170000000

static void	kfs_sleep(int second)
{
	for (int i = 0; i < second * ONE_SECOND; i ++) {
		asm("nop");
	}
}

static void	hexdump_cmd(char *arg1, char *arg2)
{
	uint32_t addr = 0;
	uint32_t size = 0;

	// Check if command good formatted
	if (*arg1 == 0 || *arg2 == 0) {
		kfs_putstr_ln("Usage   : hexdump addr size");
		kfs_putstr_ln("Example : hexdump 1000 60");
	}
	else {
		addr = kfs_atoi(arg1);
		size = kfs_atoi(arg2);

		for (int i = 0; i < size / 16; i++) {
			hexdump((void *)addr);
			addr += 16;
		}
	}
}

// write addr "message"
static void	write_cmd(const char *addr_str, const char *str)
{
	uint32_t	addr = 0;

	if (*str == 0 || *addr_str == 0) {
		kfs_putstr_ln("Usage   : write addr string");
		kfs_putstr_ln("Example : write 1000 hello_world");
	} else {
		addr = kfs_atoi(addr_str);
		kfs_memmove((void *)addr, str, kfs_strlen(str));
		kfs_putstr_ln("write success !");
	}
}

void	exec_cmd(char split[3][128])
{
	if (!(kfs_strcmp(split[0], "hexdump"))) {
		hexdump_cmd(split[1], split[2]);
	} else if (!(kfs_strcmp(split[0], "write"))) {
		write_cmd(split[1], split[2]);
	} else if (split[0][0] != 0) {
		kfs_putstr(split[0]);
		kfs_putstr_ln(": Command not found");
	}
}

void	shell(void)
{
	char	cmd[128] = {0};
	char	split[3][128] = {0};

	// wait for user command
	get_input(cmd);

	// clean command (removing extra white space)
	kfs_remove_extra_white_space(cmd);

	// split for parse command
	strsplit(cmd, split, ' ');

	// execute command
	exec_cmd(split);
}

