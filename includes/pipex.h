/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndemont <ndemont@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 12:30:55 by ndemont           #+#    #+#             */
/*   Updated: 2021/10/28 12:30:59 by ndemont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <sys/errno.h>

typedef struct s_data
{
	int		fd_in;
	int		fd_out;
	char	*cmd1;
	char	*cmd2;
	char	**env;
}				t_data;

int		print_error(int num, char *name, char *err);
char	**ft_split(char const *s, char c);
t_data	*init_data(char **av, char **env);
int		free_data(t_data *data);
int		exec_pipex(t_data *data);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		str_len(char *str);

#endif