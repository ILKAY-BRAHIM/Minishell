/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:14:58 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/16 23:29:05 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"
#include <fcntl.h>
#include <sys/stat.h>

// \6 = space       
// \1 = quote     
// \7 = null var

// norm 25 line : ----> ok
// nb function : -----> 11
// tester : ----------> ok

void	exit_ambiguous(void)
{
	fd_putstr("minishell: : ambiguous redirect\n", 2);
	exit(1);
}

void	file_err_1(char *files) // 25 line
{
	int	i;

	i = 0;
	if (ft_strlen(files) == 1 && files[0] == '\7' && files[1] == '\0')
		exit_ambiguous();
	i = 0;
	while(files[i] && files[i] == '\7')
		i++;
	if (files[i] == '\0')
		exit_ambiguous();

	i = 0;
	while(files[i] && (files[i] == '\1' || files[i] == '\7'))
		i++;
	if (files[i] == '\0')
	{
		fd_putstr("minishell: : No such file or directory\n", 2);
		exit(1);	
	}
	return ;
}

char *check_file(char *files, int i) // 24 line
{
	file_err_1(files);
	files = ft_strtrim(files, "\6");
	if (files == NULL || files[0] == '\0')
		exit_ambiguous();
	if (ft_strchr(files, '\1') != NULL)
	{
		i = ft_strlen(files) - 1;
		if ((!(files[0] == '\1'|| files[0] == '\7')
			|| !(files[i] == '\1'|| files[i] == '\7')) && ft_strchr(files, '\6') == NULL)
		{
			files = remouve_char(files, '\6');
			files = remouve_char(files, '\7');
			return (files);
		}
	}
	else
	{
		if (ft_strchr(files, '\6') != NULL)
			exit_ambiguous();
		files = remouve_char(files, '\7');
		if (files == NULL && files[0] == '\0')
			exit_ambiguous();
	}
	return (files);
}

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
	return(0);
}

void	in_file(char *file) // 25 line
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
		fd = open(file, O_RDONLY , 0644);
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

int	in_r(t_table *table, int index, int fd) // 24 line
{
	table->files[index] = check_file(table->files[index], 0);
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

void	app_file(char *file) // 25 line
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
		fd = open(file, O_WRONLY | O_APPEND, 0644);
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

int	app_r(t_table *table, int index)
{
	int	fd;

	table->files[index] = check_file(table->files[index], 0);
	table->files[index] = remouve_char(table->files[index], '\7');
	if (access(table->files[index], F_OK) != -1)
		app_file(table->files[index]);
	else
	{
		fd = open(table->files[index], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			fd_putstr("minishell: ", 2);
			fd_putstr(": No such file or directory\n", 2);
			exit(1);
		}
		dup2(fd, 1);
	}
	return(0);
}

int	redirection(t_table *table)
{
	int	i;
	int	err;
	int	fd;

	i = 0;
	err = 0;
	fd = 0;
	while(table->next[i] != 0)
	{
		if (table->next[i] == R_OUTPUT)
			err = out_r(table, i);
		else if (table->next[i] ==  R_INPUT
			|| table->next[i] == HERE_DOC_EX || table->next[i] == HERE_DOC)
			err = in_r(table, i, fd);
		else if (table->next[i] == R_APPEND)
			err = app_r(table, i);
		if (err != 0)
			exit(err);
		i++;
	}
	return (err);
}
