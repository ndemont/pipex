/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 12:32:57 by ndemont           #+#    #+#             */
/*   Updated: 2021/10/28 12:34:05 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	str_len(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	put_str(char *str)
{
	write(2, str, str_len(str));
}

int	print_error(int num, char *name, char *err)
{
	if (name)
	{
		put_str(name);
		put_str(": ");
	}
	put_str(err);
	put_str("\n");
	return (num);
}
