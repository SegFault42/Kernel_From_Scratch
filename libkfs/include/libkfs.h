#ifndef LIBKFS_H
#define LIBKFS_H

#include "string.h"
#include "scroll.h"
#include "memory.h"
#include "stdint.h"
#include "ctype.h"

#define VIDEO_MEM_BEGIN	0xb8000
#define VIDEO_MEM_END	0xb8FA0

#define MAX_LINES		25
#define MAX_COLUMNS		80

#define CURSOR_Y ((vidptr - (char *)VIDEO_MEM_BEGIN) / 2) / MAX_COLUMNS

#define BLACK			0x00
#define BLUE			0x01
#define GREEN			0x02
#define CYAN			0x03
#define RED				0x04
#define MAGENTA			0x05
#define BROWN			0x06
#define LIGHT_GREY		0x07
#define DARK_GREY		0x08
#define LIGHT_BLUE		0x09
#define LIGHT_GREEN		0x0a
#define LIGHT_CYAN		0x0b
#define LIGHT_RED		0x0c
#define LIGHT_MAGENTA	0x0d
#define LIGHT_BROWN		0x0e
#define WHITE			0x0f

extern char		*vidptr;

#endif
