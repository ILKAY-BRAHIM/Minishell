/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 23:14:58 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/19 16:50:28 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"

void	exit_ambiguous(void)
{
	fd_putstr("minishell: : ambiguous redirect\n", 2);
	exit(1);
}

void	file_err_1(char *files)
{
	int	i;

	i = 0;
	if (ft_strlen(files) == 1 && files[0] == '\7' && files[1] == '\0')
		exit_ambiguous();
	i = 0;
	while (files[i] && files[i] == '\7')
		i++;
	if (files[i] == '\0')
		exit_ambiguous();
	i = 0;
	while (files[i] && (files[i] == '\1' || files[i] == '\7'))
		i++;
	if (files[i] == '\0')
	{
		fd_putstr("minishell: : No such file or directory\n", 2);
		exit(1);
	}
	return ;
}

char	*check_file(char *files, int i)
{
	file_err_1(files);
	files = ft_strtrim(files, "\6");
	if (files == NULL || files[0] == '\0')
		exit_ambiguous();
	if (ft_strchr(files, '\1') != NULL)
	{
		i = ft_strlen(files) - 1;
		if ((!(files[0] == '\1' || files[0] == '\7') || !(files[i] == '\1'
					|| files[i] == '\7')) && ft_strchr(files, '\6') == NULL)
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
			return (i);
		}
		i++;
	}
	return (-1);
}

int	redirection(t_table *table)
{
	int	i;
	int	err;
	int	fd;

	i = 0;
	err = 0;
	fd = 0;
	while (table->next[i] != 0)
	{
		if (table->next[i] == R_OUTPUT)
			err = out_r(table, i);
		else if (table->next[i] == R_INPUT
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
