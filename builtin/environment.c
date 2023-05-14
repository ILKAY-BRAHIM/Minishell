/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 07:06:01 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/14 22:44:11 by rrasezin         ###   ########.fr       */
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
			free_one_list (befor);
		}
		else
			befor->next = tmp->next;
	}
	return ;
}

void	new_env_var(t_env *env, char *env_var, int type)
{
	t_env	*tmp;
	t_env	*new;

	new = new_list(env_var, type);
	tmp = env;
	while (tmp->name && ft_strncmp(new->name, tmp->name, -1) != 0)
	{
		if (tmp->next == NULL)
		{
			add_back(&env, new);
			return ;
		}
		tmp = tmp->next;
	}
	free(tmp->value);
	tmp->value = ft_strdup(new->value);
	tmp->type = type;
	free_one_list(new);
	return ;
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
		if (type == 0)
			return (tmp->value);
		if (type == 1)
			return (ft_strdup(tmp->value));
	}
	return (NULL);
}

t_env	*init_env(char **org_env)
{
	t_env	*env;
	char	*n_pwd;
	char	*shell_val;
	int		i;
	int		shell_value;

	i = 0;
	env = new_list(org_env[i], 0);
	if (!env)
		return (NULL);
	i++;
	while (org_env[i])
	{
		add_back(&env, new_list(org_env[i], 0));
		i++;
	}
	rm_env_var(&env, "OLDPWD");
	if (search_and_return(env, "SHLVL", 0))
	{
		shell_value = ft_atoi(search_and_return(env, "SHLVL", 0));
		shell_val = ft_strjoin("SHLVL=", ft_itoa(shell_value + 1));
		new_env_var(env, shell_val, 0);
	}
	else
	{
		shell_val = ft_strjoin("SHLVL=", ft_itoa(1));
		new_env_var(env, shell_val, 0);
	}
	if (search_and_return(env, "PWD", 0) == NULL)
	{
		n_pwd = getcwd(NULL, 0);
		new_env_var(env, ft_strjoin("PWD=", n_pwd), 0);
	}
	if (search_and_return(env, "OLDPWD", 0) == NULL)
		new_env_var(env, "OLDPWD=", 1);
	new_env_var(env, ft_strjoin("?=", ft_strdup("0")), 2);
	return (env);
}
