/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:54:40 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/02 18:06:49 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_sp(t_token *token)
{
	t_token *tmp;
	char	*part;
	char	*tm;

	tmp = token;
	tm = NULL;
	while(1)
	{
		part = strchr("<>|",token->token[0]);
		if (part != NULL)
		{
			if (tm != NULL)
			{
				printf("minishell: syntax error near unexpected token `%c'\n", token->token[0]);
				return (-1);
			}
			if (strlen(token->token) == 2)
			{
				if (!(token->token[0] == token->token[1] && token->token[0]!= '|'))
				{
					printf("minishell: syntax error near unexpected token `%c'\n", token->token[1]);
					return (-1);
				}
			}
			if (strlen(token->token) == 3)
			{
				printf("minishell: syntax error near unexpected token `%c'\n", token->token[2]);
				return(-1);
			}
			if (strlen(token->token) > 3)
			{
				if (token->token[0] == '|')
					printf("minishell: syntax error near unexpected token `%c'\n", token->token[2]);
				else
					printf("minishell: syntax error near unexpected token `%c%c'\n", token->token[2],token->token[2] );
				return(-1);
			}
			if (token->next == NULL)
			{
				printf("minishell: syntax error near unexpected token `newline'\n");
				return(-1);
			}
			tm = part;
		}
		else
			tm = NULL;
		token = token->next;
		if (token == NULL)
			break;
	}
	token = tmp;
	return (0);
}