/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:54:40 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/10 23:58:36 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_sp(t_token *token)
{
	t_token *tmp;
	char	*part;
	char	*tm;
	int		i;

	tmp = token;
	tm = NULL;
	i = 0;
	if(token->token[0] == '|')
	{
		// write(2, "unexpected EOF while looking for matching\n", 42); 
		fd_putstr("minishell: syntax error near unexpected token `", 2);
		fd_putchar(token->token[0], 2);
		fd_putstr("'\n", 2);
		// printf("minishell: syntax error near unexpected token `%c'\n", token->token[0]);
		return (-1);
	}
	while(1)
	{
		part = strchr("<>|",token->token[0]);
		if (part != NULL)
		{
			if (tm != NULL)
			{
				if (!(((token->token[0] == '<' && token->token[1] == '<' )||( token->token[0] == '>' && token->token[1] == '>') || token->token[0] == '>' || token->token[0] == '<') && tm[0] == '|'))
				{
					// write(2, "unexpected EOF while looking for matching\n", 42); 
					fd_putstr("minishell: syntax error near unexpected token `", 2);
					fd_putchar(token->token[0], 2);
					fd_putstr("'\n", 2);
					// printf("minishell: syntax error near unexpected token `%c'\n", token->token[0]);
					return (-1);
				}
				
			}
			if (strlen(token->token) == 2)
			{
				if (!(token->token[0] == token->token[1] && token->token[0]!= '|'))
				{
					// printf("minishell: syntax error near unexpected token `%c'\n", token->token[1]);
					fd_putstr("minishell: syntax error near unexpected token `", 2);
					fd_putchar(token->token[1], 2);
					fd_putstr("'\n", 2);
					return (-1);
				}
			}
			if (strlen(token->token) == 3)
			{
				// printf("minishell: syntax error near unexpected token `%c'\n", token->token[2]);
					fd_putstr("minishell: syntax error near unexpected token `", 2);
					fd_putchar(token->token[2], 2);
					fd_putstr("'\n", 2);
				return(-1);
			}
			if (strlen(token->token) > 3)
			{
				if (token->token[0] == '|')
				{
					// printf("minishell: syntax error near unexpected token `%c'\n", token->token[2]);
					fd_putstr("minishell: syntax error near unexpected token `", 2);
					fd_putchar(token->token[2], 2);
					fd_putstr("'\n", 2);
				}
				else
				{
					// printf("minishell: syntax error near unexpected token `%c%c'\n", token->token[2],token->token[2] );
					fd_putstr("minishell: syntax error near unexpected token `", 2);
					fd_putchar(token->token[2], 2);
					fd_putchar(token->token[2], 2);
					fd_putstr("'\n", 2);
				}
				return(-1);
			}
			if (token->next == NULL)
			{
				fd_putstr("minishell: syntax error near unexpected token `newline'\n", 2);
				return(-1);
			}
			tm = part;
		}
		else
			tm = NULL;
		token = token->next;
		i = 0;
		if (token != NULL && token->next == NULL)
		{
			while(token->token && token->token[i] == ' ')
				i++;
			if (token->token[i] == '\0')
			{
				fd_putstr("minishell: syntax error near unexpected token `newline'\n", 2);
				return(-1);
			}
		}
		if (token == NULL)
			break;
	}
	token = tmp;
	return (0);
}