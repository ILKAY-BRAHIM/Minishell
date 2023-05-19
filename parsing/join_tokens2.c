/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 09:28:39 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/19 16:44:53 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	_norm(char *str, t_token **new, int *count, char **tmp)
{
	if (*count == 1 && (*count)++)
		*new = new_token(*tmp);
	else
		lst_add_back(*new, new_token(*tmp));
	lst_add_back(*new, new_token(str));
	free(*tmp);
	*tmp = ft_calloc(1, 1);
}

t_token	*join_tokens2(t_token *lst, int count)
{
	t_token	*new;
	t_token	*lst_tmp;
	char	*tmp;

	tmp = ft_calloc(1, 1);
	lst_tmp = lst;
	while (lst != NULL)
	{
		if (lst->token[0] == '|')
			_norm(lst->token, &new, &count, &tmp);
		else
		{
			tmp = sp_strjoin(tmp, " ", 0);
			tmp = sp_strjoin(tmp, lst->token, 0);
		}
		lst = lst->next;
	}
	if (count == 1)
		new = new_token(tmp);
	else
		lst_add_back(new, new_token(tmp));
	free(tmp);
	free_lst(lst_tmp);
	return (new);
}
