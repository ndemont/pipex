#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <sys/errno.h>

typedef struct	s_data
{
	int		fd_in;
	int		fd_out;
	char*	cmd1;
	char*	cmd2;
	char**	env;
}				t_data;

int		print_error(int num, char* name, char* err);
char**	ft_split(char const *s, char c);
t_data*	init_data(char **av, char** env);
int		free_data(t_data *data);
int		pipex(t_data* data);

#endif