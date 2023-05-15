// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   join_tokens.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/04/20 23:29:20 by bchifour          #+#    #+#             */
// /*   Updated: 2023/04/29 07:46:42 by bchifour         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../minishell.h"

t_token	*join_tokens(t_token *tokens)
{
	t_token	*new;
	char	*array;
	int		count;
	char	*tmp;
	t_token	*tmp_lst;

	tmp_lst = tokens;
	count = 1;
	tmp = NULL;
	while (1)
	{
		array = strchr("<>|", tokens->token[0]);
		if (array == NULL)
		{
			if (tmp != NULL)
				tmp = sp_strjoin(tmp, tokens->token, 0);
			else
				tmp = strdup(tokens->token);
		}
		if (array != NULL)
		{
			if (tmp != NULL)
			{
				if (count == 1)
				{
					new = new_token(tmp);
					free(tmp);
					tmp = NULL;
					count = 2;
				}
				else
				{
					lst_add_back(new, new_token(tmp));
					free(tmp);
					tmp = NULL;
				}
			}
			if (count == 1)
			{
				new = new_token(tokens->token);
				count = 2;
			}
			else
			{
				lst_add_back(new, new_token(tokens->token));
			}
		}
		tokens = tokens->next;
		if (tokens == NULL)
		{
			if (tmp != NULL)
			{
				if (count == 1)
				{
					new = new_token(tmp);
					free(tmp);
				}
				else
				{
					lst_add_back(new, new_token(tmp));
					free(tmp);
				}
			}
			break ;
		}
	}
	free_lst(tmp_lst);
	return (new);
}
