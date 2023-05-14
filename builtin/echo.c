/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 09:26:35 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/14 15:47:41 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// changed

int	ft_echo(t_table *table, t_env *env)
{
	int	i;
	int	j;
	int	new_line;

	i = 0;
	j = 1;
	new_line = 2;
	if (table->option[i] != NULL)
	{
		while (table->option[i] && ft_strncmp(table->option[i], "-n", 2) == 0)
		{
			j = 1;
			while (table->option[i][j] == 'n')
				j++;
			if (table->option[i][j] == '\0')
			{
				new_line = 0;
				i++;
			}
			else 
				break;
		}
		while (table->option[i])
		{
			fd_putstr(table->option[i], 1);
			i++;
				fd_putstr(" ", 1);
		}			
	}
	i = 0;
	while (table->arg && table->arg[i])
	{
		table->arg[i] = remouve_char(table->arg[i] , '\1');
		if (table->arg[i][0] != '\0')
			fd_putstr(table->arg[i], 1);
		i++;
		if (table->arg[i] != NULL)
			fd_putstr(" ", 1);
	}
	if (new_line != 0)
		fd_putstr("\n", 1);
	if (env)
		rm_env_var(&env, "_");
	if (search_and_return(env, "_"))
		new_env_var(env, ft_strjoin("_=", ft_strdup("echo")), 0);
	return (0);
}
