#include "../include/kernel.h"

char	*vidptr = (char *)VIDEO_MEM_BEGIN;

/*void	kmain(t_multiboot multiboot);*/


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
