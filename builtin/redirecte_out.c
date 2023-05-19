/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecte_out.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:50:42 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/18 22:18:45 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"
#include <fcntl.h>
#include <sys/stat.h>

void	out_file(char *file)
{
	int			fd;
	struct stat	stat_f;

	if (stat(file, &stat_f) == 0)
	{
		if (S_ISDIR(stat_f.st_mode))
		{
			fd_putstr("minishell: ", 2);
			fd_putstr(file, 2);
			fd_putstr(": Is a directory\n", 2);
			exit (1);
		}
	}
	if (access(file, W_OK) != -1)
	{
		fd = open(file, O_WRONLY | O_TRUNC, 0644);
		dup2(fd, 1);
	}
	else
	{
		fd_putstr("minishell: ", 2);
		fd_putstr(file, 2);
		fd_putstr(": Permission denied\n", 2);
		exit (1);
	}
}

int	out_r(t_table *table, int index)
{
	int	fd;

	table->files[index] = check_file(table->files[index], 0);
	if (access(table->files[index], F_OK) != -1)
		out_file(table->files[index]);
	else
	{
		fd = open(table->files[index], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			fd_putstr("minishell: ", 2);
			fd_putstr(": No such file or directory\n", 2);
			exit (1);
		}
		dup2(fd, 1);
	}
	return (0);
}
