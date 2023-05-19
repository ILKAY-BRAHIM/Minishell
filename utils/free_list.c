/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 22:39:37 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/18 22:40:18 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_one_list(t_env *list)
{
	if (list)
	{
		if (list->name)
		{
			free(list->name);
			list->name = NULL;
		}
		if (list->value)
		{
			free(list->value);
			list->value = NULL;
		}
		if (list)
		{
			free (list);
			list = NULL;
		}
	}
	return ;
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (1)
	{
		free_one_list(tmp);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return ;
}
