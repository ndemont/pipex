/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 12:37:54 by ndemont           #+#    #+#             */
/*   Updated: 2021/10/28 17:30:19 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd_path(char **env_path, char	*cmd)
{
	int		i;
	int		ret;
	char	*cmd_path;

	i = 0;

	while (env_path[i])
	{
		cmd_path = ft_strjoin("/", cmd);
		cmd_path = ft_strjoin(env_path[i], cmd_path);
		ret = access(cmd_path, X_OK);
		if (ret == 0)
			return (cmd_path);
		i++;
	}
	print_error(errno, NULL, strerror(errno));
	return NULL;
}

int	execute_cmd(t_data *data)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
			return (print_error(errno, NULL, strerror(errno)));
	pid = fork();
	if (pid < 0)
		return (print_error(errno, NULL, strerror(errno)));
	if (!pid)
	{
		dup2(data->fd_in, 0);
		dup2(pipe_fd[1], 1);
		if (execve(get_cmd_path(data->env_path, *data->cmd1), data->cmd1, data->env) < 0)
		{
			print_error(errno, NULL, strerror(errno));
			exit(1);
		}
	}
	close(data->fd_in);
	close(pipe_fd[1]);
	waitpid(pid, 0, 0);
	pid = fork();
	if (pid < 0)
		return (print_error(errno, NULL, strerror(errno)));
	if (!pid)
	{
		dup2(pipe_fd[0], 0);
		dup2(data->fd_out, 1);
		if (execve(get_cmd_path(data->env_path, *data->cmd2), data->cmd2, data->env) < 0)
		{
			print_error(errno, NULL, strerror(errno));
			exit(1);
		}
	}
	waitpid(pid, 0, 0);
	close(pipe_fd[0]);
	close(data->fd_out);
	return (0);
}

int	exec_pipex(t_data	*data)
{
	execute_cmd(data);
	return (1);
}
