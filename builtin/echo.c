/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 09:26:35 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/19 16:51:13 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_options(t_table *table, int *new_line)
{
	int	i;
	int	j;

	i = 0;
	while (table->option[i] && ft_strncmp(table->option[i], "-n", 2) == 0)
	{
		j = 1;
		while (table->option[i][j] == 'n')
			j++;
		if (table->option[i][j] == '\0')
		{
			*new_line = 0;
			i++;
		}
		else
			break ;
	}
	while (table->option[i])
	{
		fd_putstr(table->option[i], 1);
		i++;
		if (table->option[i] != NULL || table->arg[0] != NULL )
			fd_putstr(" ", 1);
	}	
}

int	ft_echo(t_table *table, t_env **env)
{
	int	i;
	int	new_line;

	i = 0;
	new_line = 2;
	if (table->option[i] != NULL)
		print_options(table, &new_line);
	while (table->arg && table->arg[i])
	{
		table->arg[i] = remouve_char(table->arg[i], '\1');
		if (table->arg[i][0] != '\0')
			fd_putstr(table->arg[i], 1);
		i++;
		if (table->arg[i] != NULL)
			fd_putstr(" ", 1);
	}
	if (new_line != 0)
		fd_putstr("\n", 1);
	if (env && search_and_return(*env, "_", 0))
		rm_env_var(env, "_");
	new_env_var(env, ft_strjoin("_=", ft_strdup("echo")), 0);
	return (0);
}
