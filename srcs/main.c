#include "pipex.h"

int	main(int ac, char **av, char**env)
{
	int		ret;
	t_data*	data;

	if (ac != 5)
		return(print_error(1, NULL, "Wrong number of arguments"));
	data = init_data(av, env);
	if (!data)
		return (1);
	ret = exec_pipex(data);
	free_data(data);
	return (0);
}