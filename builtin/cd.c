/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:24:47 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/19 16:51:13 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"
#include <sys/stat.h>

int	check_stat(t_table *table)
{
	struct stat	path_stat;

	if (stat(table->arg[0], &path_stat) == 0)
	{
		if (!(S_ISDIR(path_stat.st_mode)))
			return (not_valid(table->commend, table->arg[0], 3));
		else
		{
			if (access(table->arg[0], X_OK) != 0)
				return (not_valid(table->commend, table->arg[0], 2));
		}
		if (chdir(table->arg[0]) != 0)
			return (1);
	}
	else
		return (not_valid(table->commend, table->arg[0], 0));
	return (0);
}

int	change_env(t_env **env, char *c_pwd)
{
	char	*n_pwd;

	if (*env && search_and_return(*env, "OLDPWD", 0))
		new_env_var(env, sp_strjoin("OLDPWD=", c_pwd, 1), 0);
	if (*env && search_and_return(*env, "PWD", 0))
	{
		n_pwd = getcwd(NULL, 0);
		new_env_var(env, sp_strjoin("PWD=", n_pwd, 1), 0);
	}
	return (0);
}

int	ft_cd(t_table *table, t_env **env)
{
	char	*c_pwd;

	if (table->option[0] != NULL)
		return (print_help(table, 1));
	if (*env && search_and_return(*env, "_", 0))
		rm_env_var(env, "_");
	new_env_var(env, ft_strjoin("_=", ft_strdup("cd")), 0);
	c_pwd = getcwd(NULL, 0);
	if (table->arg[0] == NULL)
	{
		if (chdir(search_and_return(*env, "HOME", 0)) != 0)
		{
			free(c_pwd);
			write(2, "minishell: cd: HOME not set\n", 28);
			return (1);
		}
	}
	else if (check_stat(table) == 1)
	{
		free(c_pwd);
		return (1);
	}
	return (change_env(env, c_pwd));
}
