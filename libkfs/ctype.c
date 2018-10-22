#include "libkfs.h"

int isascii(int c)
{
	return ((c ^ 0x80) >> 7);
}

int isprint(int c)
{
	return (c > 0x1F && c < 0x7F);
}
