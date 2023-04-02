/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 23:48:50 by rrasezin          #+#    #+#             */
/*   Updated: 2023/04/02 01:19:29 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	list_size(t_env *list)
{
	int	i;

	i = 1;
	if (!list)
		return (0);
	while (list->next)
	{
		i++;
		list = list->next;
	}
	return (i);
}

t_env	*last_list(t_env *list)
{
	int	i;

	i = list_size(list);
	if (i == 0)
		return NULL;
	while (i > 1)
	{
		list = list->next;
		i--;
	}
	return (list);
}

void	add_back(t_env **list, t_env *new)
{
	t_env	*last;

	if (!list)
		return ;
	last = last_list(*list);
	if (last)
	{
		last->next = new;
	}
	else
		*list = new;
}

void	add_front(t_env **list, t_env *new) //it's possible to use it
{
	if (new && list)
	{
		new->next = *list;
		*list = new;
	}
	else if (new)
		*list = new;
	return ;
}

t_env	*new_list(char *org_env) // one of the env name
{
	t_env	*env;
	int		size;
	int		j;

	j = 0;
	env = ft_calloc(sizeof(t_env), 1);
	size = ft_strlen(ft_strchr(org_env, '='));
	env->name = ft_calloc(ft_strlen(org_env) - size + 1, sizeof(char));
	env->value = ft_calloc(size, sizeof(char));
	while (org_env[j] && org_env[j] != '=')
	{
		env->name[j] = org_env[j];
		j++;
	}
	if (org_env[j] && org_env[j] == '=')
		j++;
	size = 0;
	while (org_env[j])
		env->value[size++] = org_env[j++];
	env->next = NULL;
	return (env);
}