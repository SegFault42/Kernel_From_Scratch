#include "../include/kernel.h"

void	keyboard(void)
{
	unsigned char	status;
	char			keycode;

	status = read_port(KEYBOARD_STATUS_PORT);
	if (status & 0x01) {
		keycode = read_port(KEYBOARD_DATA_PORT);

		if(keycode < 0)
			return;

		/*// if bit 8 is set to 1 the key is released*/
		/*if (keycode & 0x80) {*/
			/*kfs_putstr_color("Released\n", GREEN);*/
		/*}*/

		// if F1 or F2 pressed
		if (keycode == 0x3b || keycode == 0x3c)
			switch_workspace(keycode);
		// print keyboard
		else if (keyboard_map[keycode])
			kfs_putchar(keyboard_map[keycode]);
	}
}

