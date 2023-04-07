/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 23:19:21 by rrasezin          #+#    #+#             */
/*   Updated: 2023/04/07 18:25:40 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_table *table, t_env *env, int i)
{
	t_env	*tmp;

	tmp = env;
	if (table[i].option != NULL || table[i].arg != NULL )
	{
		print_help(table, i);
		return ;
	}
	if (table[i].o_file == NULL)
	{
		while (1)
		{
			printf("%s=", tmp->name);
			printf("%s\n", tmp->value);
			if (tmp->next == NULL)
				break ;
			tmp = tmp->next;
		}
	}
	//need to add the part when i have deffrent o_file in the pipe and rederection case
	return ;
}