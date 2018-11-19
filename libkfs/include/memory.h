#ifndef MEMORY_H
#define MEMORY_H

#include "stdint.h"

void	*kfs_memmove(void *dest, const void *src, size_t n);
void	*memset(void *b, int c, size_t len);

#endif
