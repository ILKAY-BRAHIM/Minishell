/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:14:58 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/13 00:49:31 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"
#include <fcntl.h>


// \6 = space       
// \1 = quote     
// \7 = null var

char *check_file(char *files)
{
	int	i;

	files = ft_strtrim(files, "\6");
	if (files == NULL || files[0] == '\0')
	{
		fd_putstr("minishell: ", 2);
		fd_putstr(": ambiguous redirect\n", 2);
		exit(1);
	}
	if (ft_strchr(files, '\1') != NULL)
	{
		i = ft_strlen(files) - 1;
		// ykon harf fajnab wmatkounch \6 falwasst
		if ((!(files[0] == '\1'|| files[0] == '\7') || !(files[i] == '\1'|| files[i] == '\7')) && ft_strchr(files, '\6') == NULL)
		{
			files = remouve_char(files, '\6');
			files = remouve_char(files, '\7');
			return (files);
		}
	}
	else
	{
		if (ft_strchr(files, '\6') != NULL)
		{
			fd_putstr("minishell: ", 2);
			fd_putstr(": ambiguous redirect\n", 2);
			exit(1);
		}
		files = remouve_char(files, '\7');
		if (files == NULL && files[0] == '\0')
		{
			fd_putstr("minishell: ", 2);
			fd_putstr(": ambiguous redirect\n", 2);
			exit(1);
		}
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

int	out_r(t_table *table, int index)
{
	int	fd;

	table->files[index] = check_file(table->files[index]);

	// table->files[index] = ft_strtrim(table->files[index], "\6");
	// if (table->files[index][0] == '\0' || ft_strchr(table->files[index], '\6') != NULL )
	// {
	// 	fd_putstr("minishell: ", 2);
	// 	fd_putstr(": ambiguous redirect\n", 2);
	// 	exit(1);
	// }
	// // table->files[index][0] == '\0' || ft_strchr(table->files[index], '\7') != NULL || 
	// if ((ft_strchr(table->files[index], '\1') != NULL && ft_strlen(table->files[index]) == 2))
	// {
	// 	fd_putstr("minishell: ", 2); // echo > ""
	// 	fd_putstr(": No such file or directory\n", 2);
	// 	exit(1);
	// }
	// if (ft_strchr(table->files[index], '\7') != NULL && ft_strlen(table->files[index]) == 1)
	// {
	// 	fd_putstr("minishell: ", 2);
	// 	fd_putstr(": ambiguous redirect\n", 2);
	// 	exit(1);
	// } 
	// table->files[index] = remouve_char(table->files[index], '\1');
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
		if (fd == -1) // failled
		{
			fd_putstr("minishell: ", 2);
			fd_putstr(": No such file or directory\n", 2);
			exit (1);
		}
		dup2(fd, 1);
	}
	return(0);
}

int	in_r(t_table *table, int index)
{
	int	fd;

	// table->files[index] = ft_strtrim(table->files[index], "\6");
	// if (table->files[index][0] == '\0' || ft_strchr(table->files[index], '\6') != NULL)
	// {
	// 	fd_putstr("minishell: ", 2);
	// 	fd_putstr(": ambiguous redirect\n", 2);
	// 	exit(1);
	// }
	// if (ft_strchr(table->files[index], '\1') != NULL)
	// {
	// 	fd_putstr("minishell: ", 2);
	// 	fd_putstr(": No such file or directory\n", 2);
	// 	exit(1);
	// }
	// table->files[index] = remouve_char(table->files[index], '\7');


	table->files[index] = check_file(table->files[index]);
	
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

	// int i = 0;
	// table->files[index] = ft_strtrim(table->files[index], "\6");
	// if (table->files[index][0] == '\0' || ft_strchr(table->files[index], '\6') != NULL)
	// {
	// 	fd_putstr("minishell: ", 2);
	// 	fd_putstr(": ambiguous redirect\n", 2);
	// 	exit(1);
	// }
	// if (ft_strchr(table->files[index], '\1') != NULL)
	// {
	// 	fd_putstr("minishell: ", 2);
	// 	fd_putstr(": No such file or directory\n", 2);
	// 	exit(1);
	// }
	
	table->files[index] = check_file(table->files[index]);

	table->files[index] = remouve_char(table->files[index], '\7');
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
		if (fd == -1) // failed
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
