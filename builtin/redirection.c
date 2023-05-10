/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:14:58 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/10 14:35:15 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"
#include <fcntl.h>

int	int_search(int *symbols, int s, int *index)
{
	int	i;

	i = 0;
	while (symbols[i] != 0)
	{
		if (symbols[i] == s)
		{
			symbols[i] = 7;
			*index = i;
			return(i);
		}
		i++;
	}
	return (-1);
}

void	out_r(t_table *table, int index)
{
	int	fd;

	if (access(table->files[index], F_OK) != -1)
	{
		if (access(table->files[index], W_OK) != -1)
		{
			fd = open(table->files[index], O_WRONLY | O_TRUNC, 0644);
			dup2(fd, 1);
		}
		else
			write (2, "permission denide\n", 18);
	}
	else
	{
		fd = open(table->files[index], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			write(2, "failed\n", 7);
		dup2(fd, 1);
	}
}

void	in_r(t_table *table, int index)
{
	int	fd;

	if (access(table->files[index], F_OK) != -1)
	{
		if (access(table->files[index], R_OK) != -1)
		{
			fd = open(table->files[index], O_RDONLY , 0644);
			dup2(fd, 0);
		}
		else
			write (2, "Permission denied\n", 18);
	}
	else
		write (2, "No such file or directory\n", 26);
}

void	app_r(t_table *table, int index)
{
	int	fd;

	if (access(table->files[index], F_OK) != -1)
	{
		if (access(table->files[index], W_OK) != -1)
		{
			fd = open(table->files[index], O_WRONLY | O_APPEND, 0644);
			dup2(fd, 1);
		}
		else
			write (2, "permission denide\n", 18);
	}
	else
	{
		fd = open(table->files[index], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			write(2, "failed\n", 7);
		dup2(fd, 1);
	}
}

void	redirection(t_table *table)
{
	int	i;

	i = 0;
	while(table->next[i] != 0)
	{
		if (table->next[i] == R_OUTPUT)
			out_r(table, i);
		if (table->next[i] ==  R_INPUT || table->next[i] == HERE_DOC_EX || table->next[i] == HERE_DOC)
			in_r(table, i);
		else if (table->next[i] == R_APPEND)
			app_r(table, i);
		i++;
	}
}
