/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 12:35:41 by ndemont           #+#    #+#             */
/*   Updated: 2021/10/28 12:36:11 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_data	*init_data(char **av, char	**env)
{
	t_data	*data;

	data = malloc(sizeof(data));
	if (!data)
	{
		print_error(errno, NULL, strerror(errno));
		return (data);
	}
	data->fd_in = open(av[1], O_RDONLY);
	if (data->fd_in < 0)
	{
		print_error(errno, av[1], strerror(errno));
		return (data);
	}
	data->fd_out = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	data->cmd1 = av[2];
	data->cmd2 = av[3];
	data->env = env;
	return (data);
}
