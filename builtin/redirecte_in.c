/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecte_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:48:11 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/18 22:18:39 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"
#include <fcntl.h>
#include <sys/stat.h>

void	in_file(char *file)
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
	if (access(file, R_OK) != -1)
	{
		fd = open(file, O_RDONLY, 0644);
		dup2(fd, 0);
	}
	else
	{
		fd_putstr("minishell: ", 2);
		fd_putstr(file, 2);
		fd_putstr(": Permission denied\n", 2);
		exit (1);
	}
}

int	in_r(t_table *table, int index, int fd)
{
	table->files[index] = check_file(table->files[index], 0);
	if (access(table->files[index], F_OK) != -1)
	{
		if (access(table->files[index], R_OK) != -1)
		{
			fd = open(table->files[index], O_RDONLY, 0644);
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
	return (0);
}
