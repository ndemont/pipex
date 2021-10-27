# include "pipex.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	begin;

	i = 0;
	if (needle[i] == '\0')
		return ((char*)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		begin = i;
		if (haystack[i] == needle[j])
		{
			while (haystack[i] == needle[j] && i < len && \
					haystack[i] && needle[j])
			{
				i++;
				j++;
			}
			if (needle[j] == '\0')
				return (&((char*)haystack)[begin]);
		}
		i = begin + 1;
	}
	return (NULL);
}