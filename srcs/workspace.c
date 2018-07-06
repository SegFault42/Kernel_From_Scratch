#include "../include/kernel.h"

static workspace		work[2] = {
	[0].ptr = (char *)VIDEO_MEM_BEGIN,
	[0].buff_video = {0},
	[1].ptr = (char *)VIDEO_MEM_BEGIN,
	[1].buff_video = {0},
};

uint8_t			current_work = 1;

void	switch_workspace(int keycode)
{
	if (keycode == 0x3b && current_work == 2) {
		//save
		work[0].ptr = vidptr;
		kfs_memmove(work[0].buff_video, (char*)VIDEO_MEM_BEGIN, (MAX_LINES * MAX_COLUMNS) * 2);
		//new
		vidptr = work[1].ptr;
		kfs_memmove((char*)VIDEO_MEM_BEGIN, work[1].buff_video ,(MAX_LINES * MAX_COLUMNS) * 2);
		current_work = 1;
	} else if (keycode == 0x3c && current_work == 1) {
		//save
		work[1].ptr = vidptr;
		kfs_memmove(work[1].buff_video, (char*)VIDEO_MEM_BEGIN, (MAX_LINES * MAX_COLUMNS) * 2);
		//new
		vidptr = work[0].ptr;
		kfs_memmove((char*)VIDEO_MEM_BEGIN, work[0].buff_video ,(MAX_LINES * MAX_COLUMNS) * 2);
		current_work = 2;
	}
}
