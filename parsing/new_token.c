/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 21:55:48 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/08 23:48:27 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void lst_add_back(t_token *lst, t_token *new)
{
	if (!lst)
	{
		lst = new;
		return;
	}
	while (lst->next)
		lst = lst->next;
	lst->next = new;
}

t_token	*new_token(char *data)
{
	t_token *token;
	token = calloc(1, sizeof(t_token));
	token->token = strdup(data);
	token->next = NULL;
	return (token);
}