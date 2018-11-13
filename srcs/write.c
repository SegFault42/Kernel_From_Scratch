#include "../include/kernel.h"

//this function write a character to x and y coordinate
void	write_to_pos(uint8_t x, uint8_t y, const char *str)
{
	uint16_t	pos = 0;
	char		*tmp = (char *)VIDEO_MEM_BEGIN;

	pos = ((y * MAX_COLUMNS) * 2) + (x * 2);
	while (*str) {
		tmp[pos] = *str;
		tmp[pos+1] = LIGHT_GREY;

		pos += 2;
		++str;
	}
}

