/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:14:58 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/10 13:28:14 by rrasezin         ###   ########.fr       */
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

void	out_r(t_table *table, int out, int index)
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

void	in_r(t_table *table, int out, int index)
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

void	app_r(t_table *table, int out, int index)
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

void	redirection(t_table *table, t_env *env)
{
	int	herdoc;
	int	i;

	// i = 0;
	// while(table->next[i] != 0)
	// {
	// 	if (table->next[i] == HERE_DOC || table->next[i] == HERE_DOC_EX)
	// 	{
	// 		id = fork();
	// 		if (id == 0)
	// 		{
	// 			herdoc = open("/tmp/heardoc_", O_CREAT | O_TRUNC | O_RDWR, 0644);
	// 			here_doc(env, herdoc, table->files[i], table->next[i]);
	// 			exit(0);	
	// 		}
	// 		pause();
	// 		waitpid(id, &status, 0);
	// 	}
	// 	i++;
	// }
	i = 0;
	while(table->next[i] != 0)
	{
		if (table->next[i] == R_OUTPUT)
			out_r(table, 1, i);
		if (table->next[i] ==  R_INPUT || table->next[i] == HERE_DOC_EX || table->next[i] == HERE_DOC)
			in_r(table, 1, i);
		else if (table->next[i] == R_APPEND)
			app_r(table, 1, i);
		i++;
	}
}
