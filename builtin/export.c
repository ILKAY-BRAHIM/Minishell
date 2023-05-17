/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:27:00 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/17 18:30:39 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"

void	add_in_env(t_table *table, t_env **env, int i, int *err)
{
	char	*check_name;

	check_name = get_part(table->arg[i], table->arg[i][0], '=', 2);
	if (check_valid_name(check_name) == 0)
	{
		table->arg[i] = remouve_char(table->arg[i], '+');
		new_env_var(env, ft_strdup(table->arg[i]), 0);
	}
	else
	{
		not_valid(table->commend, table->arg[i], 1);
		(*err) = 1;
	}
	free(check_name);
}

void	add_in_export(t_table *table, t_env **env, int i, int *err)
{
	if (check_valid_name(table->arg[i]) == 0)
	{
		table->arg[i] = remouve_char(table->arg[i], '+');
		if (search_and_return(*env, table->arg[i], 0) == NULL)
			new_env_var(env, ft_strdup(table->arg[i]), 1);
	}
	else
	{
		not_valid(table->commend, table->arg[i], 1);
		*err = 1;
	}
}

int	ft_export(t_table *table, t_env **env)
{
	int		i;
	int		err;

	err = 0;
	i = 0;
	if (*env && search_and_return(*env, "_", 0))
		rm_env_var(env, "_");
	if (table->option[0] != NULL)
	{
		print_help(table, 1);
		return (2);
	}
	if (table->arg[0] == NULL)
		return (without_args(*env));
	while (table->arg[i])
	{
		if (ft_strchr(table->arg[i], '=') != NULL)
			add_in_env(table, env, i, &err);
		else
			add_in_export(table, env, i, &err);
		i++;
	}
	return (err);
}
