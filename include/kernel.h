#ifndef KERNEL_H
#define KERNEL_H

#include "../libkfs/include/libkfs.h"
#include "../include/keyboard.h"
#include "../include/splash.h"
#include "../include/gdt.h"

typedef struct	workspace
{
	char		*ptr;
	char		buff_video[(MAX_COLUMNS * MAX_LINES) * 2];
}				workspace;

typedef struct				s_multiboot
{
	uint32_t				flags;
	uint32_t				mem_lower;
	uint32_t				mem_upper;
	uint32_t				boot_device;
	uint32_t				cmdline;
	uint32_t				mods_count;
	uint32_t				mods_addr;
	uint32_t				num;
	uint32_t				size;
	uint32_t				addr;
	uint32_t				shndx;
	uint32_t				mmap_length;
	uint32_t				mmap_addr;
	uint32_t				drives_length;
	uint32_t				drives_addr;
	uint32_t				config_table;
	uint32_t				boot_loader_name;
	uint32_t				apm_table;
	uint32_t				vbe_control_info;
	uint32_t				vbe_mode_info;
	uint32_t				vbe_mode;
	uint32_t				vbe_interface_seg;
	uint32_t				vbe_interface_off;
	uint32_t				vbe_interface_len;
}							t_multiboot;

void	clear_screen(void);
void	write_to_pos(uint8_t x, uint8_t y, const char *str);
void	switch_workspace(int keycode);
void	shell();
//exvoid	init_gdt(void);

#endif
