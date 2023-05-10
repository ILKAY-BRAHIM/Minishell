/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 17:55:05 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/10 16:27:56 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"

int	ft_unset(t_table *table, t_env **env)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	rm_env_var(env, "_");
	new_env_var(*env, ft_strjoin("_=", ft_strdup("unset")), 0);
	if (table->option[0] != NULL)
	{
		print_help(table, 1);
		return (2);
	}
	while (table->arg[i])
	{
		if (check_valid_name(table->arg[i]) != 0)
		{
			not_valid(table->commend, table->arg[i], 1);
			err = 1;
		}
		else
			rm_env_var(env, table->arg[i]);
		i++;
	}
	return (err);
}

/* $? return	*/