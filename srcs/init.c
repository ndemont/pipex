/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 12:35:41 by ndemont           #+#    #+#             */
/*   Updated: 2021/10/29 15:11:26 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_env_path(char **env)
{
	int		i;
	char	*path_line;
	char	**path_tab;

	i = 0;
	while (env[i])
	{
		path_line = ft_strnstr(env[i], "PATH", strlen(env[i]));
		if (path_line == env[i])
		{
			path_tab = ft_split(&(env[i][5]), ':');
			return (path_tab);
		}
		i++;
	}
	return (NULL);
}

t_data	*print_and_free(t_data *data, char *str)
{
	print_error(errno, str, strerror(errno));
	free_data(data);
	return (NULL);
}

t_data	*init_data(char **av, char	**env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (print_and_free(data, NULL));
	data->fd_in = 0;
	data->fd_out = 0;
	data->fd_in = open(av[1], O_RDONLY);
	if (data->fd_in < 0)
		print_error(errno, av[1], strerror(errno));
	data->fd_out = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->fd_out < 0)
		print_error(errno, av[4], strerror(errno));
	data->cmd1 = ft_split(av[2], ' ');
	if (!data->cmd1)
		return (print_and_free(data, NULL));
	data->cmd2 = ft_split(av[3], ' ');
	if (!data->cmd2)
		return (print_and_free(data, NULL));
	data->env_path = get_env_path(env);
	if (!data->env_path)
		return (print_and_free(data, NULL));
	data->env = env;
	return (data);
}
