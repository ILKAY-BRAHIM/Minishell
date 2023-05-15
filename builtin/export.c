/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:27:00 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/15 16:35:37 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"

// changed --------------------
char *add_quote_slash(char *value)
{
	char	*result;
	int	size;
	int	i;

	i = 0;
	size = 0;
	while(value[i])
	{
		if (value[i] == '\"' || value[i] == '$')
			size++;
		i++;
		size++;
	}
	result = ft_calloc(size + 1, sizeof(char));
	i = 0;
	size = 0;
	while (value[i])
	{
		if (value[i] == '\"' || value[i] == '$')
		{
			result[size] = '\\';
			size++;
		}
		result[size] = value[i];
		i++;
		size++;
	}
	free(value);
	return(result);
}
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
	tmp = env;
	export = ft_calloc(size + 1, sizeof(char *));
	while (i < size - 1)
	{
		if (tmp->type == 2)
			tmp = tmp->next;
		if (tmp->type == 1)
			export[i] = sp_strjoin("declare -x ", tmp->name, -1);
		else if (tmp->type == 0)
		{
			export[i] = sp_strjoin("declare -x ", tmp->name, -1);
			export[i] = sp_strjoin(export[i], "=", 0);
			export[i] = sp_strjoin(export[i], "\"", 0);
			if (ft_strchr(tmp->value, '$') || ft_strchr(tmp->value, '"'))
				tmp->value = add_quote_slash(tmp->value);
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
	if (env && search_and_return(env, "_", 0))
		rm_env_var(&env, "_");
	new_env_var(env, ft_strjoin("_=", ft_strdup("export")), 0);	
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
			fd_putstr(sorted[i], 1);
			fd_putchar('\n', 1);
			i++;
		}
		return (0);
	}
	while (table->arg[i])
	{
		if (ft_strchr(table->arg[i], '=') != NULL)
		{
			check_name = get_part(table->arg[i], table->arg[i][0], '=', 2);
			if (check_valid_name(check_name) == 0)
			{
				table->arg[i] = remouve_char(table->arg[i], '+');
				new_env_var(env, ft_strdup(table->arg[i]), 0);
			}
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
			{
				table->arg[i] = remouve_char(table->arg[i], '+');
				if (search_and_return(env, table->arg[i], 0) == NULL)
					new_env_var(env, ft_strdup(table->arg[i]), 1);
			}
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