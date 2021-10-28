/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 12:36:24 by ndemont           #+#    #+#             */
/*   Updated: 2021/10/28 12:37:35 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int		ret;
	t_data	*data;

	if (ac != 5)
		return (print_error(1, NULL, "Wrong number of arguments"));
	data = init_data(av, env);
	if (!data)
		return (1);
	ret = exec_pipex(data);
	free_data(data);
	return (0);
}
