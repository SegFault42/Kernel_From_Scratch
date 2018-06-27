#include "libft.h"

void	*ft_kmemmove(void *dest, const void *src, size_t n)
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
