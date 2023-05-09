/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 09:28:39 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/08 22:57:19 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *join_tokens2(t_token *lst)
{
	t_token *new;
	t_token *lst_tmp;
	char	*tmp;
	int		count;

	tmp = calloc(1, 1);
	count = 1;
	lst_tmp = lst;
	while(1)
	{
		if (lst->token[0] == '|')
		{
			if (count == 1)
			{
				new = new_token(tmp);
				count = 2;
			}
			else
				lst_add_back(new, new_token(tmp));
			lst_add_back(new, new_token(lst->token));
			free(tmp);
			tmp = calloc(1, 1);
		}
		else 
		{
			tmp = sp_strjoin(tmp, " ", 0);
			tmp = sp_strjoin(tmp, lst->token, 0);
		}
		lst = lst->next;
		if (lst == NULL)
		{
			if (count == 1)
				new = new_token(tmp);
			else
				lst_add_back(new, new_token(tmp));
			free(tmp);
			tmp = NULL;
			break ;
		}
	}
	free(tmp);
	free_lst(lst_tmp);
	return(new);
}