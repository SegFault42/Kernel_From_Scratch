#include "../include/kernel.h"

void	get_input(char buff[])
{
	unsigned char	status;
	char			keycode;
	uint8_t			idx = 0;

	for (;;) {
		status = read_port(KEYBOARD_STATUS_PORT);
		if (status & 0x01) {
			keycode = read_port(KEYBOARD_DATA_PORT);

			if (!(keycode & 0x80)) {
				kfs_putchar(keyboard_map[keycode]);
				if(keycode < 0) {
					kfs_putstr("return\n");
					return;
				}

				// store keyboard input
				else if (keyboard_map[keycode] > 0) {
					buff[idx] = keyboard_map[keycode];
					idx++;
				}

				// break loop if enter is pressed
				if (buff[idx -1] == '\n')
					break ;
			}
		}
		if (idx == 126) {
			kfs_putstr_color("\nCommand to long\n", RED);
			kfs_memset(buff, 0, sizeof(buff));
			break ;
		}
	}
}

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

