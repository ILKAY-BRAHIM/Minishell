/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 07:06:01 by rrasezin          #+#    #+#             */
/*   Updated: 2023/04/05 14:45:07 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/utils.h"

t_env	*init_env(char **org_env)
{
	t_env	*env;
	int		i;

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
	return (env);
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

// #include <stdio.h>
// int	main(int ac, char **av, char **envv)
// {
// 	t_env	*env;
// 	t_env	*ennv;
// 	int		i;

// 	ennv = init_env(envv);
// 	env = ennv;
// 	new_env_var(env, "SHLVL=3");
// 	if (ac == 2)
// 		rm_env_var(env, av[1]);
// 	i = 0;

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
// 	while (1);
// }
