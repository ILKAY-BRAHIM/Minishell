/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 07:06:01 by rrasezin          #+#    #+#             */
/*   Updated: 2023/04/02 01:43:15 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/utils.h"

static	int env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

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

// #include <stdio.h>
// int	main(int ac, char **av, char **envv)
// {
// 	t_env	*env;
// 	int		i;

// 	env = init_env(envv);
// 	i = 0;

// 	while (1)
// 	{
// 		printf("%s=", env->name);
// 		printf("%s\n", env->value);
// 		printf("%s\n", envv[i++]);
// 		if (!env->next)
// 			break ;
// 		env = env->next;
// 	}
// }
