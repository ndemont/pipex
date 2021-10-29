/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 12:37:54 by ndemont           #+#    #+#             */
/*   Updated: 2021/10/29 18:34:31 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex_exit(t_data *data, char *cmd_path)
{
	free_data(data);
	if (cmd_path)
		free(cmd_path);
	return (errno);
}

char	*get_cmd_path(char **env_path, char	*cmd)
{
	int		i;
	int		ret;
	char	*cmd_path;
	char	*tmp;

	i = 0;
	while (env_path[i])
	{
		cmd_path = ft_strjoin("/", cmd);
		tmp = cmd_path;
		cmd_path = ft_strjoin(env_path[i], cmd_path);
		free(tmp);
		ret = access(cmd_path, X_OK);
		if (ret == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

int	execute_cmd1(t_data *data, int *pipe_fd, char **cmd)
{
	pid_t	pid;
	char	*cmd_path;

	pid = fork();
	cmd_path = get_cmd_path(data->env_path, *cmd);
	if (pid < 0)
		return (print_error(errno, NULL, strerror(errno)));
	if (!pid)
	{
		if (!cmd_path)
		{
			if (data->fd_in > 0)
				print_error(errno, *cmd, "Command not found");
			exit(pipex_exit(data, cmd_path));
		}
		if (dup2(data->fd_in, 0) < 0)
			exit(pipex_exit(data, cmd_path));
		if (dup2(pipe_fd[1], 1) < 0)
			exit(pipex_exit(data, cmd_path));
		if (execve(cmd_path, cmd, data->env) < 0)
			exit(pipex_exit(data, cmd_path));
	}
	waitpid(pid, 0, 0);
	if (cmd_path)
		free(cmd_path);
	return (0);
}

int	execute_cmd2(t_data *data, int *pipe_fd, char **cmd)
{
	pid_t	pid;
	char	*cmd_path;

	pid = fork();
	cmd_path = get_cmd_path(data->env_path, *cmd);
	if (pid < 0)
		return (print_error(errno, NULL, strerror(errno)));
	if (!pid)
	{
		if (!cmd_path)
		{
			print_error(errno, *cmd, "Command not found");
			exit(pipex_exit(data, cmd_path));
		}
		if (dup2(pipe_fd[0], 0) < 0)
			exit(pipex_exit(data, cmd_path));
		if (dup2(data->fd_out, 1) < 0)
			exit(pipex_exit(data, cmd_path));
		if (execve(cmd_path, cmd, data->env) < 0)
			exit(pipex_exit(data, cmd_path));
	}
	waitpid(pid, 0, 0);
	if (cmd_path)
		free(cmd_path);
	return (0);
}

int	exec_pipex(t_data	*data)
{
	int		pipe_fd[2];
	int		ret;

	if (pipe(pipe_fd) == -1)
		return (print_error(errno, NULL, strerror(errno)));
	ret = execute_cmd1(data, pipe_fd, data->cmd1);
	close(pipe_fd[1]);
	ret = execute_cmd2(data, pipe_fd, data->cmd2);
	close(pipe_fd[0]);
	return (ret);
}
