/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:28:40 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/19 16:51:13 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"

void	add_backslash(char **result, char *value)
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

char	*export_line(t_env *env, int i, int size)
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
		while (env->value[i])
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

char	**export_val(t_env *env)
{
	t_env	*tmp;
	char	**export;
	int		i;
	int		size;

	size = list_size(env);
	if (size == 0)
		return (NULL);
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
	while (sorted && sorted[i] != NULL)
	{
		fd_putstr(sorted[i], 1);
		fd_putchar('\n', 1);
		i++;
	}
	free_array(sorted);
	return (0);
}
