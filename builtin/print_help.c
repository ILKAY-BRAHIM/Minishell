/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:55:16 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/19 16:50:28 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"

void	fd_putchar(char c, int fd)
{
	write (fd, &c, 1);
}

int	check_valid_name(char *name)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[i]) != 0
		|| (ft_isalpha(name[i]) == 0 && name[i] != '_'))
		return (1);
	i++;
	while (name[i] != '\0')
	{
		if (ft_isalpha(name[i]) == 0
			&& ft_isdigit(name[i]) == 0 && name[i] != '_' && name[i] != '+')
			return (1);
		i++;
	}
	if (ft_strchr(name, '+') != NULL && ft_strlen(ft_strchr(name, '+')) > 1)
		return (1);
	return (0);
}

void	continue_(char *arg, int type)
{
	if (type == 3 && arg)
	{
		fd_putstr(arg, 2);
		fd_putstr(" : Not a directory\n", 2);
	}
	else if (type == 4)
		fd_putstr("command not found\n", 2);
	else if (type == 5 && arg)
	{
		fd_putstr(arg, 2);
		fd_putstr(": is a directory\n", 2);
	}
	return ;
}

int	not_valid(char *cmd, char *arg, int type)
{
	fd_putstr("minishell: ", 2);
	if (cmd)
	{
		fd_putstr(cmd, 2);
		fd_putstr(": ", 2);
	}
	if (type == 0 && arg)
	{
		fd_putstr(arg, 2);
		fd_putstr(": No such file or directory\n", 2);
	}
	else if (type == 1 && arg)
	{
		fd_putstr(" `", 2);
		fd_putstr(arg, 2);
		fd_putstr("': not a valid identifier\n", 2);
	}
	else if (type == 2 && arg)
	{
		fd_putstr(arg, 2);
		fd_putstr(" : Permission denied\n", 2);
	}
	else
		continue_(arg, type);
	return (1);
}

int	print_help(t_table *table, int i)
{
	fd_putstr("minishell: ", 2);
	fd_putstr(table->commend, 2);
	if (table->option[0] != NULL)
	{
		fd_putstr(": illegal option -- ", 2);
		fd_putchar(table->option[0][1], 2);
		fd_putchar('\n', 2);
		fd_putstr(table->commend, 2);
	}
	fd_putstr(": usage: ", 2);
	fd_putstr(table->commend, 2);
	fd_putstr(" [no option]", 2);
	if (i == 1)
		fd_putstr(" [name ...]\n", 2);
	else
		fd_putchar('\n', 2);
	return (1);
}
