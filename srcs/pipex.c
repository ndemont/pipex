/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 12:37:54 by ndemont           #+#    #+#             */
/*   Updated: 2021/10/28 12:39:44 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute_cmd(int in, int out, char **cmd, char **env)
{
	pid_t	pid;
	int		i;

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
	i = 0;
	while (cmd[i])
		free(cmd[i++]);
	return (0);
}

int	exec_pipex(t_data	*data)
{
	int	fd_tmp;

	fd_tmp = data->fd_out;
	execute_cmd(data->fd_in, 1, ft_split(data->cmd1, ' '), data->env);
	execute_cmd(data->fd_out, fd_tmp, ft_split(data->cmd2, ' '), data->env);
	return (1);
}
