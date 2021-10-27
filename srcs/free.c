#include "pipex.h"

int		free_data(t_data *data)
{
	close(data->fd_in);
	close(data->fd_out);
	free(data);
	data = NULL;
	return (1);
}