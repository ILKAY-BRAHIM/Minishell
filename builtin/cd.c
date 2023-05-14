/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:24:47 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/14 22:28:00 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"
#include <sys/stat.h>

// changed

int	ft_cd(t_table *table, t_env *env)
{
	char	n_pwd[100];
	char	c_pwd[100];
	struct stat path_stat;

	if (table->option[0] != NULL)
	{
		print_help(table, 1);
		return (1);
	}
	if (env && search_and_return(env, "_", 0))
		rm_env_var(&env, "_");
	new_env_var(env, ft_strjoin("_=", ft_strdup("cd")), 0);
	getcwd(c_pwd, sizeof(c_pwd));
	if (table->arg[0] == NULL)
	{
		if (chdir(search_and_return(env, "HOME", 0)) != 0)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			return (1);
		}
	}
	else if (stat(table->arg[0], &path_stat) == 0)
	{
		if (!(S_ISDIR(path_stat.st_mode)))
		{
			not_valid(table->commend, table->arg[0], 3);
			return (1);
		}
		else
		{
			if (access(table->arg[0], X_OK) != 0)
			{
				not_valid(table->commend, table->arg[0], 2);
				return (1);
			}
		}
		if (chdir(table->arg[0]) != 0)
			return (1);
	}
	else
	{
		not_valid(table->commend, table->arg[0], 0);
		return (1);
	}
	if (env && search_and_return(env, "OLDPWD", 0))
		new_env_var(env, ft_strjoin("OLDPWD=", ft_strdup(c_pwd)), 0);
	if (env && search_and_return(env, "PWD", 0))
	{
		getcwd(n_pwd, sizeof(n_pwd));
		new_env_var(env, ft_strjoin("PWD=", ft_strdup(n_pwd)), 0);	
	}
	return (0);
}

// int	main(int ac, char **av)
// {
// 	char	n_pwd[1024];
// 	char	c_pwd[1024];

// 	getcwd(c_pwd, sizeof(c_pwd));
// 	chdir(av[1]);
// 	getcwd(n_pwd, sizeof(n_pwd));
// 	printf("current : %s\n", c_pwd);
// 	printf("new     : %s\n", n_pwd);
// }