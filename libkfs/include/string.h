#ifndef STRING_H
#define STRING_H

#include "stdint.h"

void	kfs_putstr(const char *str);
void	kfs_putstr_ln(const char *str);
void	kfs_putstr_color(const char *str, uint8_t color);

void	kfs_putchar(int c);
void	kfs_putchar_ln(int c);
void	kfs_putchar_color(int c, uint8_t color);

void	kfs_putnbr(int nb);
void	kfs_putnbr_ln(int nb);

size_t	kfs_strlen(const char *str);

int		kfs_strcmp(const char *s1, const char *s2);
char	*kfs_strcpy(char *dst, const char *src);

char	*to_hex_8(uint8_t key);
char	*to_hex_16(uint16_t key);
char	*to_hex_32(uint32_t key);

void	hexdump(void *addr);

void	kfs_remove_extra_white_space(char *str);

int		kfs_atoi(const char *str);

int		count_nb_elem(char *str, char c);
void	strsplit(char *cmd, char split[3][128], char c);

#endif
