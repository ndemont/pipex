/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 12:34:34 by ndemont           #+#    #+#             */
/*   Updated: 2021/10/28 13:12:40 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	free_data(t_data *data)
{
	int i;

	if (data)
	{
		close(data->fd_in);
		close(data->fd_out);
		i = 0;
		while (data->cmd1 && data->cmd1[i])
			free(data->cmd1[i++]);
		free(data->cmd1);
		i = 0;
		while (data->cmd2[i])
			free(data->cmd2[i++]);
		free(data->cmd2);
		free(data);
	}
	return (errno);
}
