/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:27:00 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/09 16:24:20 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"

// changed --------------------

char **export_val(t_env *env)
{
	t_env	*tmp;
	char	**export;
	int		i;
	int		size;

	size = list_size(env);
	if (size == 0)
		return NULL;
	i = 0;
	tmp = env; // sort or no [!] -----------------------
	export = ft_calloc(size + 1, sizeof(char *));
	while (i < size)
	{
		export[i] = sp_strjoin("declare -x ", tmp->name, -1);
		if (tmp->type == 0)
		{
			export[i] = sp_strjoin(export[i], "=", 0);
			export[i] = sp_strjoin(export[i], "\"", 0);
			export[i] = sp_strjoin(export[i], tmp->value, 0);
			export[i] = sp_strjoin(export[i], "\"", 0);
		}
		tmp = tmp->next;
		i++;
	}
	export[i] = NULL;
	return (export);
}

int	ft_export(t_table *table, t_env *env)
{
	char	**sorted;
	char	*check_name;
	int		i;
	int		err;

	err = 0;
	i = 0;
	if (table->option[0] != NULL)
	{
		print_help(table, 1);
		return (2);
	}
	if (table->arg[0] == NULL)
	{
		sorted = export_val(env);
		while (sorted  && sorted[i] != NULL)
		{
			printf("%s\n", sorted[i]);
			i++;
		}
		return (0);
	}
	rm_env_var(env, "_");
	new_env_var(env, ft_strjoin("_=", ft_strdup("export")), 0);
	if (ft_isdigit(table->arg[0][0]) != 0)
	{
		not_valid(table->commend, table->arg[0], 1);
		return (1);
	}
	while (table->arg[i])
	{
		if (ft_strchr(table->arg[i], '=') != NULL)
		{
			check_name = get_part(table->arg[i], table->arg[i][0], '=', 2);
			if (check_valid_name(check_name) == 0)
				new_env_var(env, table->arg[i], 0);
			else
			{
				not_valid(table->commend, table->arg[i], 1);
				err = 1;
			}
			free(check_name);
		}
		else
		{
			if (check_valid_name(table->arg[i]) == 0)
				new_env_var(env, table->arg[i], 1);
			else
			{
				not_valid(table->commend, table->arg[i], 1);
				err = 1;
			}
		}
		i++;
	}
	return (err);
}