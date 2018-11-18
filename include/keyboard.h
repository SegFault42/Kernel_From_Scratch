#ifndef KEYBOARD_H
#define KEYBOARD_H

#define IDT_SIZE					256
#define KEYBOARD_DATA_PORT			0x60
#define KEYBOARD_STATUS_PORT		0x64
#define INTERRUPT_GATE				0x8e
#define KERNEL_CODE_SEGMENT_OFFSET	0x08
#define ENTER_KEY_CODE				0x1C

static const unsigned char	keyboard_map[] = {
	0, // undefined
	0, // escape
	'1','2','3','4','5','6','7','8','9','0','-','=',
	'\b', // backspace
	'\t', // tab
	'q','w','e','r','t','y','u','i','o','p','[',']','\n',
	0, // Ctrl
	'a','s','d','f','g','h','j','k','l',';','\'','`',
	0, // Left shift
	'\\','z','x','c','v','b','n','m',',','.','/',
	0,		// Right shift
	'*',	// (Keypad *)
	0,		// left alt
	' ',
	'0',	// Caps lock
	0,		// <F1>
	0,		// <F2>
	0,		// <F3>
	0,		// <F4>
	0,		// <F5>
	0,		// <F6>
	0,		// <F7>
	0,		// <F8>
	0,		// <F9>
	0,		// <F10>
	0,		// Num lock
	0,		// Scroll Lock
	0,		// Home key
	0,		// Up Arrow
	0,		// Page Up
	'-',
	0,		// Left Arrow
	0,
	0,		// Right Arrow
	'+',
	0,		// End key
	0,		// Down Arrow
	0,		// Page Down
	0,		// Insert Key
	0,		// Delete Key
	0,		// ?
	0,		// ?
	0,		// ?
	0,		// <F11>
	0		// <F12>
};

extern char	read_port(unsigned short port);
extern void	write_port(unsigned short port, unsigned char data);
void		keyboard(void);
void		get_input(char buff[]);

#endif
