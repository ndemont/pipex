/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 12:34:34 by ndemont           #+#    #+#             */
/*   Updated: 2021/10/28 17:05:21 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_tab(char **tab)
{
	int	i;

	if (tab)
	{
		i = 0;
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

int	free_data(t_data *data)
{
	if (data)
	{
		if (data->fd_in)
			close(data->fd_in);
		if (data->fd_out)
			close(data->fd_out);
		free_tab(data->cmd1);
		free_tab(data->cmd2);
		free_tab(data->env_path);
		free(data);
	}
	return (0);
}
