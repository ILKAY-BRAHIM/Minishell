/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 07:06:01 by rrasezin          #+#    #+#             */
/*   Updated: 2023/06/09 22:32:27 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rm_env_var(t_env **env, char *env_var)
{
	t_env	*tmp;
	t_env	*befor;

	tmp = *env;
	befor = tmp;
	while (env && ft_strncmp(env_var, tmp->name, -1) != 0)
	{
		befor = tmp;
		if (tmp->next == NULL)
			return ;
		tmp = tmp->next;
	}
	if (env && ft_strncmp(env_var, tmp->name, -1) == 0)
	{
		if (befor == *env)
		{
			*env = (*env)->next;
			tmp = befor;
		}
		else
			befor->next = tmp->next;
		free_one_list (tmp);
	}
	return ;
}

void	new_env_var(t_env **env, char *env_var, int type)
{
	t_env	*tmp;
	t_env	*new;

	new = new_list(env_var, type);
	tmp = *env;
	if (*env == NULL)
	{
		*env = new;
		return (free(env_var));
	}
	while (tmp && tmp->name && ft_strncmp(new->name, tmp->name, -1) != 0)
	{
		if (tmp->next == NULL)
		{
			add_back(env, new);
			return (free(env_var));
		}
		tmp = tmp->next;
	}
	free(tmp->value);
	tmp->value = ft_strdup(new->value);
	tmp->type = type;
	free_one_list(new);
	return (free(env_var));
}

char	*search_and_return(t_env *env, char *env_var, int type)
{
	t_env	*tmp;

	if (env)
	{
		tmp = env;
		while (tmp->name && ft_strncmp(env_var, tmp->name, -1) != 0)
		{
			if (tmp->next == NULL)
				return (NULL);
			tmp = tmp->next;
		}
		if (tmp->name && ft_strncmp(env_var, tmp->name, -1) == 0)
		{
			if (type == 0)
				return (tmp->value);
			if (type == 1)
			{
				if (tmp->value && tmp->value[0] != '\0')
					return (ft_strdup(tmp->value));
				else
					return (NULL);
			}
		}
	}
	return (NULL);
}

void	if_not_exist(t_env **env)
{
	char	*n_pwd;
	char	*shell_var;

	if (search_and_return(*env, "SHLVL", 0))
	{
		shell_var = sp_strjoin("SHLVL=",
				ft_itoa(ft_atoi(search_and_return(*env, "SHLVL", 0)) + 1), 1);
		new_env_var(env, shell_var, 0);
	}
	else
	{
		shell_var = sp_strjoin("SHLVL=", ft_itoa(1), 1);
		new_env_var(env, shell_var, 0);
	}
	if (search_and_return(*env, "PWD", 0) == NULL)
	{
		n_pwd = getcwd(NULL, 0);
		if (n_pwd != NULL)
		{
			shell_var = sp_strjoin("PWD=", n_pwd, 1);
			new_env_var(env, shell_var, 0);
		}
	}
	return ;
}

t_env	*init_env(char **org_env)
{
	t_env	*env;
	char	*shell_var;
	int		i;

	i = 0;
	if (org_env[0] != NULL)
	{
		env = new_list(org_env[i], 0);
		i++;
	}
	else
		env = new_list("_=env", 0);
	if (!env)
		return (NULL);
	while (org_env[i] != NULL)
		add_back(&env, new_list(org_env[i++], 0));
	if_not_exist(&env);
	if (search_and_return(env, "OLDPWD", 0) != NULL)
		rm_env_var(&env, "OLDPWD");
	if (search_and_return(env, "OLDPWD", 0) == NULL)
		new_env_var(&env, ft_strdup("OLDPWD"), 1);
	shell_var = sp_strjoin("?=", "0", -1);
	new_env_var(&env, shell_var, 2);
	return (env);
}
