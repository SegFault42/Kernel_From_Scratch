#ifndef KEYBOARD_H
#define KEYBOARD_H

#define IDT_SIZE					256
#define KEYBOARD_DATA_PORT			0x60
#define KEYBOARD_STATUS_PORT		0x64
#define INTERRUPT_GATE				0x8e
#define KERNEL_CODE_SEGMENT_OFFSET	0x08
#define ENTER_KEY_CODE				0x1C

typedef struct		IDT_entry
{
	unsigned short int offset_lowerbits;
	unsigned short int selector;
	unsigned char zero;
	unsigned char type_attr;
	unsigned short int offset_higherbits;
}					IDT_entry;

extern unsigned char keyboard_map[];

extern void keyboard_handler(void);
extern char read_port(unsigned short port);
extern void write_port(unsigned short port, unsigned char data);
extern void load_idt(unsigned long *idt_ptr);

void kb_init(void);
void idt_init(void);
void keyboard_handler_main(void);

#endif
