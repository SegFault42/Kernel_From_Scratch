#include "../include/kernel.h"

struct IDT_entry	IDT[IDT_SIZE];

typedef struct	workspace
{
	char		*ptr;
	char		buff_video[(80 * 25) * 2];
}				workspace;


uint8_t			current_work = 1;
workspace		work[2] = {
	[0].ptr = (char *)VIDEO_MEM_BEGIN,
	[0].buff_video = {0},
	[1].ptr = (char *)VIDEO_MEM_BEGIN,
	[1].buff_video = {0},
};


void keyboard_handler_main(void)
{
	unsigned char	status;
	char			keycode;


	write_port(0x20, 0x20);

	status = read_port(KEYBOARD_STATUS_PORT);
	if (status & 0x01) {
		keycode = read_port(KEYBOARD_DATA_PORT);

		if(keycode < 0)
			return;

		/*// if bit 8 is set to 1 the key is released*/
		/*if (keycode & 0x80) {*/
			/*kfs_putstr_color("Released\n", GREEN);*/
		/*}*/

		if (keycode == 0x3b && current_work == 2) {
			//save
			work[0].ptr = vidptr;
			kfs_kmemmove(work[0].buff_video, (char*)VIDEO_MEM_BEGIN, (MAX_LINES * MAX_COLUMNS) * 2);
			//new
			vidptr = work[1].ptr;
			kfs_kmemmove((char*)VIDEO_MEM_BEGIN, work[1].buff_video ,(MAX_LINES * MAX_COLUMNS) * 2);
			current_work = 1;
		} else if (keycode == 0x3c && current_work == 1) {
			//save
			work[1].ptr = vidptr;
			kfs_kmemmove(work[1].buff_video, (char*)VIDEO_MEM_BEGIN, (MAX_LINES * MAX_COLUMNS) * 2);
			//new
			vidptr = work[0].ptr;
			kfs_kmemmove((char*)VIDEO_MEM_BEGIN, work[0].buff_video ,(MAX_LINES * MAX_COLUMNS) * 2);
			current_work = 2;
		} else if  (keyboard_map[keycode])
			kfs_putchar(keyboard_map[keycode]);
	}
}

void kb_init(void)
{
	write_port(0x21 , 0xFD);
}

void idt_init(void)
{
	unsigned long keyboard_address;
	unsigned long idt_address;
	unsigned long idt_ptr[2];

	keyboard_address = (unsigned long)keyboard_handler; 
	IDT[0x21].offset_lowerbits = keyboard_address & 0xffff;
	IDT[0x21].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[0x21].zero = 0;
	IDT[0x21].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[0x21].offset_higherbits = (keyboard_address & 0xffff0000) >> 16;

	write_port(0x20 , 0x11);
	write_port(0xA0 , 0x11);

	write_port(0x21 , 0x20);
	write_port(0xA1 , 0x28);

	write_port(0x21 , 0x00);
	write_port(0xA1 , 0x00);

	write_port(0x21 , 0x01);
	write_port(0xA1 , 0x01);

	write_port(0x21 , 0xff);
	write_port(0xA1 , 0xff);

	idt_address = (unsigned long)IDT;
	idt_ptr[0] = (sizeof (struct IDT_entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
	idt_ptr[1] = idt_address >> 16 ;

	load_idt(idt_ptr);
}
