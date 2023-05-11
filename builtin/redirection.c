/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:14:58 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/12 00:29:42 by rrasezin         ###   ########.fr       */
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

int	out_r(t_table *table, int index)
{
	int	fd;

	table->files[index] = remouve_char(table->files[index], '\6');
	if (access(table->files[index], F_OK) != -1)
	{
		if (access(table->files[index], W_OK) != -1)
		{
			fd = open(table->files[index], O_WRONLY | O_TRUNC, 0644);
			dup2(fd, 1);
		}
		else
		{
			fd_putstr("minishell: ", 2);
			fd_putstr(table->files[index], 2);
			fd_putstr(": Permission denied\n", 2);
			exit (1);
		}
	}
	else
	{
		fd = open(table->files[index], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			write(2, "failed\n", 7);
		dup2(fd, 1);
	}
	return(0);
}

int	in_r(t_table *table, int index)
{
	int	fd;

	table->files[index] = remouve_char(table->files[index], '\6');
	if (access(table->files[index], F_OK) != -1)
	{
		if (access(table->files[index], R_OK) != -1)
		{
			fd = open(table->files[index], O_RDONLY , 0644);
			dup2(fd, 0);
		}
		else
		{
			fd_putstr("minishell: ", 2);
			fd_putstr(table->files[index], 2);
			fd_putstr(": Permission denied\n", 2);
			exit (1);
		}
	}
	else
	{
		fd_putstr("minishell: ", 2);
		fd_putstr(table->files[index], 2);
		fd_putstr(": No such file or directory\n", 2);
		exit(1);
	}
	return(0);
}

int	app_r(t_table *table, int index)
{
	int	fd;

	table->files[index] = remouve_char(table->files[index], '\6');
	if (access(table->files[index], F_OK) != -1)
	{
		if (access(table->files[index], W_OK) != -1)
		{
			fd = open(table->files[index], O_WRONLY | O_APPEND, 0644);
			dup2(fd, 1);
		}
		else
		{
			fd_putstr("minishell: ", 2);
			fd_putstr(table->files[index], 2);
			fd_putstr(": Permission denied\n", 2);
			exit (1);
		}
	}
	else
	{
		fd = open(table->files[index], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			write(2, "failed\n", 7);
		dup2(fd, 1);
	}
	return(0);
}

int	redirection(t_table *table)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while(table->next[i] != 0)
	{
		if (table->next[i] == R_OUTPUT)
			err = out_r(table, i);
		else if (table->next[i] ==  R_INPUT || table->next[i] == HERE_DOC_EX || table->next[i] == HERE_DOC)
			err = in_r(table, i);
		else if (table->next[i] == R_APPEND)
			err = app_r(table, i);
		if (err != 0)
			exit(err);
		i++;
	}
	return (err);
}
