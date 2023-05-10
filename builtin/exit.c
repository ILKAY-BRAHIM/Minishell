/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:43:21 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/10 15:54:43 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"

int	ft_exit(t_table *table, t_env *env)
{
	long long status;

	(void)env;
	(void)table;
	rm_env_var(&env, "_");
	new_env_var(env, ft_strjoin("_=", ft_strdup("exit")), 0);
	write(1, "exit\n", 5);
	if (table->arg[0] != NULL)
	{
		if (table->arg[1] != NULL)
		{
			fd_putstr("minishell: exit: too many arguments", 2);
			return (1);
		}
		status = ft_atoi(table->arg[0]);
		if (status == -1)
		{
			fd_putstr("minishell: exit:", 2);
			fd_putstr(table->arg[0], 2);
			fd_putstr(": numeric argument required\n", 2);
			exit(255);
		}
		else
			exit(status & 255);
	}
	else 
		exit(exit_status);
	return (0);
}