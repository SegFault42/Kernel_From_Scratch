#include "../include/kernel.h"

t_gdt_entry	gdt_entries[NB_ENTRIES];
t_gdt_ptr		gdt_ptr;

static void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	gdt_entries[num].base_low = (base & 0xFFFF);
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].base_high = (base >> 24) & 0xFF;

	gdt_entries[num].limit_low = (limit & 0xFFFF);
	gdt_entries[num].granularity = (limit >> 16) & 0x0F;

	gdt_entries[num].granularity |= gran & 0xF0;
	gdt_entries[num].access = access;
}

void	init_gdt(void)
{
	gdt_ptr.limit = (sizeof(t_gdt_entry) * NB_ENTRIES) - 1;
	gdt_ptr.base = (uint32_t)GDT_BEGIN;

	gdt_set_gate(0, 0, 0, 0, 0);											// Null segment

	gdt_set_gate(1, 0, (uint32_t)0xFFFFFFFF, (uint8_t)0x9A, (uint8_t)0xCF);	// KCode segment
	gdt_set_gate(2, 0, (uint32_t)0xFFFFFFFF, (uint8_t)0x92, (uint8_t)0xCF);	// KData segment
	gdt_set_gate(2, 0, (uint32_t)0xFFFFFFFF, (uint8_t)0x96, (uint8_t)0xCF);	// KStack segment

	gdt_set_gate(3, 0, (uint32_t)0xFFFFFFFF, (uint8_t)0xFA, (uint8_t)0xCF);	// UCode segment
	gdt_set_gate(4, 0, (uint32_t)0xFFFFFFFF, (uint8_t)0xF2, (uint8_t)0xCF);	// UCata segment
	gdt_set_gate(4, 0, (uint32_t)0xFFFFFFFF, (uint8_t)0xF6, (uint8_t)0xCF);	// UStack segment

	kfs_memmove((char *)gdt_ptr.base, &gdt_entries, gdt_ptr.limit);

	gdt_flush((uint32_t)&gdt_ptr);
}
