/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 17:34:00 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/18 23:34:51 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"

void	replac_char(char **str, char old, char new)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (str[i])
	{
		while (str[i][j])
		{
			if (str[i][j] == old)
				str[i][j] = new;
			j++;
		}
		j = 0;
		i++;
	}
	return ;
}

void	arg_concatenation(t_table *table, char *cmd_lwr, char **cmd)
{
	int	i;

	i = 0;
	while (table->arg[i] != NULL)
	{
		if (strchr(table->arg[i], '\1'))
		{
			if (ft_strcmp(cmd_lwr, "echo") != 0)
				table->arg[i] = remouve_char(table->arg[i], '\1');
			if (table->arg[i][0] == '\0')
			{
				fd_putstr(table->commend, 2);
				fd_putstr(": ", 2);
				fd_putstr(": No such file or directory\n", 2);
				exit(1);
			}
		}
		table->arg[i] = remouve_char(table->arg[i], '\7');
		*cmd = sp_strjoin(*cmd, table->arg[i], 0);
		*cmd = sp_strjoin(*cmd, "\4", 0);
		i++;
	}
	return ;
}

void	call_execve(t_table *table, char *path, char **env)
{
	char	**argv;
	char	*cmd;
	char	*cmd_lwr;
	int		i;

	i = 0;
	cmd_lwr = (ft_tolower(table->commend));
	cmd = sp_strjoin(path, "\4", -1);
	while (table->option[i] != NULL)
	{
		cmd = sp_strjoin(cmd, table->option[i], 0);
		cmd = sp_strjoin(cmd, "\4", 0);
		i++;
	}
	arg_concatenation(table, cmd_lwr, &cmd);
	free(cmd_lwr);
	argv = ft_split(cmd, '\4');
	replac_char(argv, '\1', '\0');
	g_exit = 0;
	if (execve(path, argv, env) == -1)
	{
		not_valid(table->commend, NULL, 4);
		exit (127);
	}
	exit (1);
}

void	normal_execute(t_table *table, t_env **env, char *path)
{
	char	*cmd;
	char	**char_env;

	cmd = sp_strjoin(path, "/", -1);
	cmd = sp_strjoin(cmd, table->commend, 0);
	if (access(cmd, X_OK) == 0)
	{
		if (*env && search_and_return(*env, "_", 0))
			rm_env_var(env, "_");
		new_env_var(env, sp_strjoin("_=", cmd, -1), 0);
		char_env = ft_get_env(*env);
		call_execve(table, cmd, char_env);
	}
	free(cmd);
	return ;
}

void	no_path_execution(t_table *table, t_env **env, char **path)
{
	char	**char_env;

	if (ft_strchr(table->commend, '/') == NULL)
	{
		if (path == NULL)
			not_valid(NULL, table->commend, 0);
		else
			not_valid(NULL, table->commend, 4);
		exit (127);
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
	if (*env && search_and_return(*env, "_", 0))
		rm_env_var(env, "_");
	new_env_var(env, sp_strjoin("_=", table->commend, -1), 0);
	char_env = ft_get_env(*env);
	call_execve(table, table->commend, char_env);
}
