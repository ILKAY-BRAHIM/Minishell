/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 22:50:19 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/15 22:54:47 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_lst(t_token *token)
{
	t_token	*tmp_frr;

	tmp_frr = token;
	while (tmp_frr->next != NULL)
	{
		tmp_frr = tmp_frr->next;
		free(token->token);
		free(token);
		token = tmp_frr;
	}
	free(token->token);
	free(token);
}
