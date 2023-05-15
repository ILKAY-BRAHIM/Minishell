/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:19:21 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/14 22:58:38 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"

// changed

int	ft_env(t_table *table, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	(void) table;

	if (env && search_and_return(env, "_", 0))
		rm_env_var(&env, "_");
	new_env_var(env, ft_strjoin("_=", ft_strdup("env")), 0);
	if (table->option[0] != NULL || table->arg[0] != NULL )
	{
		print_help(table, 0);
		return (1);
	}
	// if (env != NULL && tmp != NULL)
	// {
		while (1)
		{
			if (tmp->type == 0)
			{
				printf("%s=", tmp->name);
				printf("%s\n", tmp->value);
			}
			// if (tmp->type == 2)// most delete it
			// {
			// 	printf("------------- %s=", tmp->name); 
			// 	printf("%s\n", tmp->value);
			// }
			if (tmp->next == NULL)
				break ;
			tmp = tmp->next;
		}	
	// }
	return (0);
}