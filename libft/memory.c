#include "libft.h"

void	*kfs_kmemset(void *b, int c, size_t len)
{
	size_t	i = 0;
	char *tmp_b = b;

	while (i < len) {
		*tmp_b++ = c;
		i++;
	}
	return (b);
}

void	*kfs_kmemmove(void *dest, const void *src, size_t n)
{
	size_t		i = 0;
	char		*tmp_dest = dest;
	const char	*tmp_src = src;

	while (i < n) {
		tmp_dest[i] = tmp_src[i];
		i++;
	}
	return (dest);
}
