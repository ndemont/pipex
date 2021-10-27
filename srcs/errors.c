#include "pipex.h"

int	str_len(char* str)
{
	int len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	put_str(char* str)
{
	write(2, str, str_len(str));
}

int	print_error(int num, char* name, char* err)
{
	if (name)
	{
		put_str(name);
		put_str(": ");
	}
	put_str(err);
	put_str("\n");
	return (num);
}