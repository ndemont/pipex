#include "pipex.h"

int		free_data(t_data *data)
{
	free(data);
	return (1);
}