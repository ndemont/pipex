#include "pipex.h"


int execute_cmd(int	in, int out, char** cmd, char** env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (print_error(errno, NULL, strerror(errno)));
	if (!pid)
	{
		if (dup2(in, 0) < 0)
			print_error(errno, NULL, strerror(errno));
		if (dup2(out, 1) < 0)
			print_error(errno, NULL, strerror(errno));
		if (execve(*cmd, cmd, env) < 0)
		{
			print_error(errno, NULL, strerror(errno));
			exit(1);
		}
	}
	waitpid(pid, 0, 0);
	int i = 0;
	while (cmd[i])
		free(cmd[i++]);
	return (0);
}

int	exec_pipex(t_data* data)
{
	char** path;

	int i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		if (ft_strnstr(data->env[i], "PATH", str_len(data->env[i])))
			break;
		i++;
	}
	path = ft_split(&(data->env[i][5]), ':');
	int fd_tmp = data->fd_out;
	execute_cmd(data->fd_in, data->fd_out, ft_split(data->cmd1, ' '), path);
	execute_cmd(data->fd_out, fd_tmp, ft_split(data->cmd2, ' '), path);
	return (1);
}