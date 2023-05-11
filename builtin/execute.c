/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 02:45:35 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/11 15:02:17 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"

char	**ft_get_path(t_env *env)
{
	char	*env_path;
	char	**path;

	env_path = search_and_return(env, "PATH");
	if (env_path)
	{
		path = ft_split(env_path, ':');
		return (path);
	}
	else
		return (NULL);
}

char	**ft_get_env(t_env *list_env)
{
	t_env	*tmp;
	char	**env;
	int		i;
	int		size;

	size = list_size(list_env);
	if (size == 0)
		return NULL;
	i = 0;
	tmp = list_env;
	env = ft_calloc(size + 1, sizeof(char *));
	while (i < size)
	{
		env[i] = sp_strjoin(tmp->name, "=", -1);
		env[i] = sp_strjoin(env[i], tmp->value, -1);
		tmp = tmp->next;
		i++;
	}
	return (env);
}

// join all option whith all args
// split them in char** 
// creat the first arg for execve
// the caracter that i split with them i need to change it [!] ------ ********** [!]
void	call_execve(t_table *table, char *path, char **env)
{
	char	**argv;
	char	*cmd;
	int		i;

	i = 0;
	cmd = sp_strjoin(path, "~", -1);
	while (table->option[i] != NULL)
	{
		cmd = sp_strjoin(cmd, table->option[i], 0);
		cmd = sp_strjoin(cmd, "~", 0);
		i++;
	}
	i = 0;
	while (table->arg[i] != NULL)
	{
		cmd = sp_strjoin(cmd, table->arg[i], 0);
		cmd = sp_strjoin(cmd, "~", 0);
		i++;
	}
	argv = ft_split(cmd, '~');
	// free(cmd);
	exit_status = 0;
	if (execve(path, argv, env) == -1)
	{
		fd_putstr("minishell: ", 2);
		fd_putstr(table->commend, 2);
		fd_putstr(": command not found\n", 2);
		//free argv & path
		exit (127);
	}
	exit (1);
}

void	ft_execute(t_table *table, t_env *env)
{
	char	**path;
	char	**char_env;
	char	*cmd;
	int		i;

	i = 0;
	if (table->commend == NULL)
		return ;
	path = ft_get_path(env);
	if (path != NULL)
	{
		while (path && path[i])
		{
			cmd = sp_strjoin(path[i], "/", -1);
			cmd = sp_strjoin(cmd , table->commend, 0);
			if (access(cmd, X_OK) == 0)
			{
				rm_env_var(&env, "_");
				new_env_var(env, sp_strjoin("_=", cmd, -1), 0);
				char_env = ft_get_env(env);
				call_execve(table, cmd, char_env);
				break;
			}
			else
				i++;
			free(cmd);
		}
		if (path == NULL || path[i] == NULL)
		{
			if (ft_strchr(table->commend, '/') == NULL)
			{
				not_valid( NULL, table->commend,4);
				exit (127);
			}
			if (access(table->commend, F_OK) != 0)
			{
				not_valid( NULL, table->commend,0);
				exit (127);
			}
			if (access(table->commend, X_OK) != 0)
			{
				not_valid( NULL, table->commend,2);
				exit (126);
			}
			rm_env_var(&env, "_");
			new_env_var(env, sp_strjoin("_=", table->commend, -1), 0);
			char_env = ft_get_env(env);
			call_execve(table, table->commend, char_env);
		}
	}
	else if (table->commend != NULL)
	{
		if (ft_strchr(table->commend, '/') == NULL)
		{
			not_valid( NULL, table->commend,4);
			exit (127);
		}
		if (access(table->commend, F_OK) != 0)
		{
			not_valid( NULL, table->commend,0);
			exit (127);
		}
		if (access(table->commend, X_OK) != 0)
		{
			not_valid( NULL, table->commend,2);
			exit (126);
		}
		rm_env_var(&env, "_");
		new_env_var(env, sp_strjoin("_=", table->commend, -1), 0);
		char_env = ft_get_env(env);
		call_execve(table, table->commend, char_env);
	}
}
