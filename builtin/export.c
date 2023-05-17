/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:27:00 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/16 17:24:51 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"

// norm 25 line : ----> ok
// nb function : -----> 7
// tester : ----------> ok

void	add_backslash(char **result, char *value) //16 line
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (value[i])
	{
		if (value[i] == '\"' || value[i] == '$')
		{
			(*result)[size] = '\\';
			size++;
		}
		(*result)[size] = value[i];
		i++;
		size++;
	}
}

char	*export_line(t_env *env, int i, int size) // 25 line
{
	char	*export;
	char	*tmp;

	i = 0;
	size = 0;
	export = sp_strjoin("declare -x ", env->name, -1);
	export = sp_strjoin(export, "=", 0);
	export = sp_strjoin(export, "\"", 0);
	if (ft_strchr(env->value, '$') || ft_strchr(env->value, '"'))
	{
		while(env->value[i])
		{
			if (env->value[i] == '\"' || env->value[i] == '$')
				size++;
			i++;
			size++;
		}
		tmp = ft_calloc(size + 1, sizeof(char));
		add_backslash(&tmp, env->value);
	}
	else
		tmp = ft_strdup(env->value);
	export = sp_strjoin(export, tmp, 2);
	export = sp_strjoin(export, "\"", 0);
	return (export);
}

char	**export_val(t_env *env) // 24 line
{
	t_env	*tmp;
	char	**export;
	int		i;
	int		size;

	size = list_size(env);
	if (size == 0)
		return NULL;
	i = 0;
	tmp = env;
	export = ft_calloc(size + 1, sizeof(char *));
	while (i < size - 1)
	{
		if (tmp->type == 2)
			tmp = tmp->next;
		if (tmp->type == 1)
			export[i] = sp_strjoin("declare -x ", tmp->name, -1);
		else if (tmp->type == 0)
			export[i] = export_line(tmp, i, size);
		tmp = tmp->next;
		i++;
	}
	export[i] = NULL;
	return (export);
}

int	without_args(t_env *env)
{
	char	**sorted;
	int		i;

	i = 0;
	sorted = export_val(env);
	while (sorted  && sorted[i] != NULL)
	{
		fd_putstr(sorted[i], 1);
		fd_putchar('\n', 1);
		i++;
	}
	free_array(sorted);
	return (0);
}

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

int	ft_export(t_table *table, t_env **env) // 23 line
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