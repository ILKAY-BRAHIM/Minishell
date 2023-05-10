/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 07:06:01 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/10 16:33:29 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rm_env_var(t_env **env, char *env_var)
{
	t_env	*tmp;
	t_env	*befor;

	tmp = *env;
	befor = tmp;
	while (ft_strncmp(env_var, tmp->name, -1) != 0)
	{
		befor = tmp;
		if (tmp->next == NULL)
			return ;
		tmp = tmp->next;
	}
	if (ft_strncmp(env_var, tmp->name, -1) == 0)
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
	while (ft_strncmp(new->name, tmp->name, -1) != 0)
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
	free_one_list(new);
	return ;
}

char	*search_and_return(t_env *env, char *env_var)
{
	t_env	*tmp;

	tmp = env;
	while (ft_strncmp(env_var, tmp->name, -1) != 0)
	{
		if (tmp->next == NULL)
			return (NULL);
		tmp = tmp->next;
	}
	if (ft_strncmp(env_var, tmp->name, -1) == 0)
		return (ft_strdup(tmp->value));
	return (NULL);
}

t_env	*init_env(char **org_env)
{
	t_env	*env;
	char	n_pwd[100];
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
	if (search_and_return(env, "SHLVL"))
	{
		shell_value = ft_atoi(search_and_return(env, "SHLVL"));
		shell_val = ft_strjoin("SHLVL=", ft_itoa(shell_value + 1));
		new_env_var(env, shell_val, 0);
	}
	else
	{
		shell_val = ft_strjoin("SHLVL=", ft_itoa(1));
		new_env_var(env, shell_val, 0);
	}
	if (search_and_return(env, "PWD") == NULL)
	{
		getcwd(n_pwd, sizeof(n_pwd));
		new_env_var(env, ft_strjoin("PWD=", ft_strdup(n_pwd)), 0);
	}
	new_env_var(env, ft_strjoin("?=", ft_strdup("0")), 2);
	return (env);
}

// #include <stdio.h>
// int	main(int ac, char **av, char **envv)
// {
// 	t_env	*env;
// 	t_env	*ennv;
// 	int		i;

// 	ennv = init_env(envv);
// 	env = ennv;
// 	// new_env_var(env, "SHLVL=3");
// 	// if (ac == 2)
// 	// 	rm_env_var(env, av[1]);
// 	i = 0;
// 	if (ac == 2)
// 		printf("%s\n\n", search_and_return(env, av[1]));
// 	while (1)
// 	{
// 		printf("%s=", env->name);
// 		printf("%s\n", env->value);
// 		// printf("%s\n", envv[i++]);
// 		if (!env->next)
// 			break ;
// 		env = env->next;
// 	}
// 	free_env(ennv);
// }
