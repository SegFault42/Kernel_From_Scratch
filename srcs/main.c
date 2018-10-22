#include "../include/kernel.h"

char	*vidptr = (char *)VIDEO_MEM_BEGIN;

/*void	kmain(t_multiboot multiboot);*/

static	void printfHex(uint8_t key)
{
    char* foo = "00";
    char* hex = "0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0xF];
    foo[1] = hex[key & 0xF];
    kfs_putstr(foo);
}

static void printfHex16(uint16_t key)
{
    printfHex((key >> 8) & 0xFF);
    printfHex( key & 0xFF);
}

static void printfHex32(uint32_t key)
{
    printfHex((key >> 24) & 0xFF);
    printfHex((key >> 16) & 0xFF);
    printfHex((key >> 8) & 0xFF);
    printfHex( key & 0xFF);
}

static void	hexdump(void *addr)
{
	// Print offset
	printfHex32((uint32_t)addr);
	kfs_putstr("  ");

	// Print value in hex
	for (int i = 0; i < 16; i++) {
		printfHex(*(uint8_t *)addr);

		if (i == 7) kfs_putstr("  ");
		else kfs_putstr(" ");
		addr++;
	}

	addr -= 16;

	kfs_putstr(" |");
	// Print value in ascii
	for (int i = 0; i < 16; i++) {
		if (isprint(*(uint8_t *)addr))
			kfs_putchar(*(uint8_t *)addr);
		else
			kfs_putchar('.');
		addr++;
	}

	kfs_putstr("|\n");
}

#define KBRD_INTRFC 0x64

/* keyboard interface bits */
#define KBRD_BIT_KDATA 0 /* keyboard data is in buffer (output buffer is empty) (bit 0) */
#define KBRD_BIT_UDATA 1 /* user data is in buffer (command buffer is empty) (bit 1) */

#define KBRD_IO 0x60 /* keyboard IO port */
#define KBRD_RESET 0xFE /* reset CPU command */

#define bit(n) (1<<(n)) /* Set bit n to 1 */

/* Check if bit n in flags is set */
#define check_flag(flags, n) ((flags) & bit(n))

void reboot(void)
{
	uint8_t temp;

	asm volatile ("cli"); /* disable all interrupts */

	/* Clear all keyboard buffers (output and command buffers) */
	do
	{
		temp = read_port(KBRD_INTRFC); /* empty user data */
		if (check_flag(temp, KBRD_BIT_KDATA) != 0)
			read_port(KBRD_IO); /* empty keyboard data */
	} while (check_flag(temp, KBRD_BIT_UDATA) != 0);

	write_port(KBRD_INTRFC, KBRD_RESET); /* pulse CPU reset line */
loop:
	asm volatile ("hlt"); /* if that didn't work, halt the CPU */
	goto loop; /* if a NMI is received, halt again */
}

void	shell(void)
{
	char	cmd[128];
	char	*tmp = 0x0;

	kfs_memset(&cmd, 0, sizeof(cmd));

	get_input(&cmd);

	if (!(kfs_strcmp(cmd, "hexdump\n"))) {
		for (int i = 0; i < 0xfff; i++) {
			hexdump(tmp);
			tmp += 16;
			for (int i = 0; i < 1000000; i++) {} // fake sleep
		}
	}
	else if (!(kfs_strcmp(cmd, "reboot\n"))) {
		reboot();
	}
}

int	kmain(t_multiboot multiboot)
{
	/*uint8_t *tmp = 0x0;*/

	init_gdt();
	kfs_clear_screen();

	for (int i = 0; i < 967; i++) {
		kfs_putchar_color(splash[i], LIGHT_GREEN);
	}

	/*kfs_strcpy(tmp, "HELLO WORLD");*/

	/*for (int i = 0; i < 0xfff; i++) {*/
	/*hexdump(tmp);*/
	/*tmp += 16;*/
	/*for (int i = 0; i < 1000000; i++) {}*/
	/*}*/

	kfs_putstr_color("$> ", GREEN);
	while (1) {
		shell();
		kfs_putstr_color("$> ", GREEN);
		/*keyboard();*/
	}

	return (0);
}
