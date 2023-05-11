/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:43:21 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/11 18:40:20 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"

int	check_exit_status(char **arg , int type)
{
	int	i;

	i = 0;
	if (type == 0)
	{
		i++;
		while(arg[0][i] && ft_isdigit(arg[0][i]) != 0)
			i++;
		if (arg[0][i])
		{
			fd_putstr("minishell: exit: ", 2);
			fd_putstr(arg[0], 2);
			fd_putstr(": numeric argument required\n", 2);
			exit(255);
		}
		else
			exit(ft_atoi(arg[0]) & 255);
	}
	else if (type == 1)
	{
		while(arg[0][i] && ft_isdigit(arg[0][i]) != 0)
			i++;
		if (arg[0][i])
		{
			fd_putstr("minishell: exit: ", 2);
			fd_putstr(arg[0], 2);
			fd_putstr(": numeric argument required\n", 2);
			exit(255);
		}
		else
			return(ft_atoi(arg[0]) & 255);
	}
	return 0;
}

int	ft_exit(t_table *table, t_env *env)
{
	long long status;

	(void)env;
	(void)table;
	rm_env_var(&env, "_");
	new_env_var(env, ft_strjoin("_=", ft_strdup("exit")), 0);
	if (table->option[0] != NULL)
		check_exit_status(table->option, 0);
	else if (table->arg[0] != NULL)
	{
		status = check_exit_status(table->arg, 1);
		if (status != 0)
		{
			if (table->arg[1] != NULL)
			{
				fd_putstr("minishell: exit: too many arguments\n", 2);
				exit_status = 1;
				return (1);
			}
			else
				exit (status);
		}
	}
	else 
		exit(exit_status);
	return (0);
}