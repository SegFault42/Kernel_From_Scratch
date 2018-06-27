#include "libft.h"

void	*ft_kmemset(void *b, int c, size_t len)
{
	size_t	i = 0;
	char *tmp_b = b;

	while (i < len) {
		*tmp_b++ = c;
		i++;
	}
	return (b);
}
