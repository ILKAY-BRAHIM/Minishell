/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:48:48 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/19 16:51:13 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	norm(char *str, t_token **new, char **tmp, int *count)
{
	if (*tmp != NULL)
	{
		if (*count == 1 && (*count)++)
			*new = new_token(*tmp);
		else
			lst_add_back(*new, new_token(*tmp));
		free(*tmp);
		*tmp = NULL;
	}
	if (*count == 1 && (*count)++)
		*new = new_token(str);
	else
		lst_add_back(*new, new_token(str));
}

t_token	*join_tokens(t_token *t, char *tmp, int count, char *array)
{
	t_token	*new;
	t_token	*tmp_lst;

	tmp_lst = t;
	while (t != NULL)
	{
		array = ft_strchr("<>|", t->token[0]);
		(array == NULL && tmp != NULL) && (tmp = sp_strjoin(tmp, t->token, 0));
		(array == NULL && tmp == NULL) && (tmp = ft_strdup(t->token));
		if (array != NULL)
			norm(t->token, &new, &tmp, &count);
		t = t->next;
	}
	if (count == 1 && tmp != NULL)
		new = new_token(tmp);
	else if (tmp != NULL)
		lst_add_back(new, new_token(tmp));
	free(tmp);
	free_lst(tmp_lst);
	return (new);
}
