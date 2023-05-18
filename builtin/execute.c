/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 02:45:35 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/18 15:33:57 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"
#include <sys/stat.h>

void	add_internal_executabel(char **env_path, char *new)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while ((*env_path)[i])
	{
		if (i == 0 && (*env_path)[i] == ':')
		{
			new[size] = '.';
			size++;
		}
		else if (size == i && (*env_path)[i + 1]
			&& (*env_path)[i] == ':' && (*env_path)[i + 1] == ':')
		{
			new[size++] = (*env_path)[i++];
			new[size] = '.';
			size++;
		}
		new[size++] = (*env_path)[i++];
	}
	free(*env_path);
	*env_path = new;
}

char	**ft_get_path(t_env *env)
{
	char	*env_path;
	char	*new;
	char	**path;

	env_path = search_and_return(env, "PATH", 1);
	if (env_path == NULL)
		return (NULL);
	new = ft_calloc(ft_strlen(env_path) + 2, sizeof(char));
	add_internal_executabel(&env_path, new);
	if (env_path)
	{
		path = ft_split(env_path, ':');
		free(env_path);
		return (path);
	}
	else
		return (NULL);
}

char	**ft_get_env(t_env *list_env)
{
	char	**env;
	int		i;
	int		size;

	i = 0;
	size = list_size(list_env);
	if (size == 0)
		return (NULL);
	env = ft_calloc(size + 1, sizeof(char *));
	while (list_env)
	{
		if (list_env->type == 0)
		{
			env[i] = sp_strjoin(list_env->name, "=", -1);
			if (list_env->value[0] != '\0')
				env[i] = sp_strjoin(env[i], list_env->value, -1);
		}
		list_env = list_env->next;
		i++;
	}
	return (env);
}

void	executabel_err_check(t_table *table)
{
	struct stat	path_stat;

	if (ft_strchr(table->commend, '/') == NULL)
	{
		not_valid(table->commend, table->commend, 4);
		exit (127);
	}
	else if (stat(table->commend, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			not_valid(NULL, table->commend, 5);
			exit (126);
		}
	}
	if (access(table->commend, F_OK) != 0)
	{
		not_valid(NULL, table->commend, 0);
		exit (127);
	}
	if (access(table->commend, X_OK) != 0)
	{
		not_valid(NULL, table->commend, 2);
		exit (126);
	}
}

void	ft_execute(t_table *table, t_env **env)
{
	char	**path;
	char	**char_env;
	int		i;

	i = 0;
	if (table->commend == NULL)
		return ;
	path = ft_get_path(*env);
	if (path != NULL)
	{
		while (path && path[i])
			normal_execute(table, env, path[i++]);
		if (path[i] == NULL)
		{
			executabel_err_check(table);
			if (*env && search_and_return(*env, "_", 0))
				rm_env_var(env, "_");
			new_env_var(env, sp_strjoin("_=", table->commend, -1), 0);
			char_env = ft_get_env(*env);
			call_execve(table, table->commend, char_env);
		}
	}
	else if (table->commend != NULL)
		no_path_execution(table, env, path);
}
