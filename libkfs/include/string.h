#ifndef STRING_H
#define STRING_H

#include "stdint.h"

// string.c
void	kfs_putstr(const char *str);
void	kfs_putstr_color(const char *str, uint8_t color);
void	kfs_putchar(int c);
void	kfs_putnbr(int c);
void	kfs_putchar_color(int c, uint8_t color);
size_t	kfs_strlen(const char *str);
int		kfs_strcmp(const char *s1, const char *s2);
char	*kfs_strcpy(char *dst, const char *src);
void	printHex(uint8_t key);
void	printHex16(uint16_t key);
void	printHex32(uint32_t key);
void	hexdump(void *addr);
void	kfs_remove_extra_white_space(char *str);

#endif
