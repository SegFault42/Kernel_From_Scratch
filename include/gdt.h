#ifndef GDT_H
#define GDT_H

#define NB_ENTRIES 7
#define GDT_BEGIN 0x00000800

typedef struct	s_gdt_entry
{
	uint16_t	limit_low;           // The lower 16 bits of the limit.
	uint16_t	base_low;            // The lower 16 bits of the base.
	uint8_t		base_middle;         // The next 8 bits of the base.
	uint8_t		access;              // Access flags, determine what ring this segment can be used in.
	uint8_t		granularity;
	uint8_t		base_high;           // The last 8 bit
} __attribute__((packed)) t_gdt_entry;

typedef struct	s_gdt_ptr
{
	uint16_t	limit;               // The upper 16 bits of all selector limits.
	uint32_t	base;                // The address of the first gdt_entry_t struct.
} __attribute__((packed)) t_gdt_ptr;

void	init_gdt(void);
extern void	gdt_flush(uint32_t);


#endif
