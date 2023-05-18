/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 23:48:50 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/18 22:40:23 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	list_size(t_env *list)
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

static t_env	*last_list(t_env *list)
{
	int	i;

	i = list_size(list);
	if (i == 0)
		return (NULL);
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

t_env	*new_list(char *org_env, int type)
{
	t_env	*env;
	int		size;
	int		j;

	j = 0;
	env = ft_calloc(sizeof(t_env), 1);
	size = ft_strlen(ft_strchr(org_env, '='));
	if (size == 0)
		size = 1;
	env->name = ft_calloc((ft_strlen(org_env) - size) + 2, sizeof(char));
	env->value = ft_calloc(size, sizeof(char));
	env->type = type;
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
