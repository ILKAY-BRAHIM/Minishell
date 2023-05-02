/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 07:06:01 by rrasezin          #+#    #+#             */
/*   Updated: 2023/04/18 23:15:23 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rm_env_var(t_env *env, char *env_var)
{
	t_env	*tmp;
	t_env	*befor;

	tmp = env;
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
		befor->next = tmp->next;
		free_one_list(tmp);
	}
	return ;
}

void	new_env_var(t_env *env, char *env_var)
{
	t_env	*tmp;
	t_env	*new;

	new = new_list(env_var);
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
	char	*shell_val;
	int		i;
	int		shell_value;

	i = 0;
	env = new_list(org_env[i]);
	if (!env)
		return (NULL);
	i++;
	while (org_env[i])
	{
		add_back(&env, new_list(org_env[i]));
		i++;
	}
	rm_env_var(env, "OLDPWD");
	if (search_and_return(env, "SHLVL"))
	{
		shell_value = ft_atoi(search_and_return(env, "SHLVL"));
		shell_val = ft_strjoin("SHLVL=", ft_itoa(shell_value + 1));
		new_env_var(env, shell_val);
	}
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
