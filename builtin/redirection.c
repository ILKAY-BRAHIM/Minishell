/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:14:58 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/08 11:49:43 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"
#include <fcntl.h>

int	int_search(int *symbols, int s)
{
	int	i;

	i = 0;
	while (symbols[i] != 0)
	{
		if (symbols[i] == s)
			return(i);
		i++;
	}
	return (-1);
}

void	here_doc(int output, char *end, int expand)
{
	char	*read;

	(void)expand; // expand in cas : $name 
	while (1)
	{
		read = readline("> ");
		if (ft_strcmp(read , end) == 0)
		{
			free(read);
			break ;
		}
		read = sp_strjoin(read, "\n", 0);
		fd_putstr(read, output);
		free(read);
	}
}

void	redirection(t_table *table, t_env *env)
{
	int	size;
	int	fd;
	// int	*order;
	int	i;

	(void)env;
	(void)table;
	printf("redirection\n");
	i = 0;
	size = 0;
	while (table->next[i++] != 0)
		size++;
	if (int_search(table->next, 4) != -1)
		printf("here doc %d\n", int_search(table->next, 4));
	fd = open("test.txt", O_CREAT | O_WRONLY | O_APPEND | O_TRUNC , 0644);
	if (fd != -1)
		here_doc(fd, "stop", 0);
}
