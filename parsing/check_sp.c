/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 21:54:40 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/15 23:42:06 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_print(char type)
{
	if (type == '\0')
	{
		fd_putstr("minishell: syntax error ", 2);
		fd_putstr("near unexpected token `newline'\n", 2);
	}
	else
		fd_putstr("minishell: syntax error near unexpected token `", 2);
	if (type != '\0')
	{
		fd_putchar(type, 2);
		fd_putstr("\n", 2);
	}
	return (-1);
}

int	check_p1(char *str)
{
	if (strlen(str) == 2)
	{
		if (!(str[0] == str[1] && str[0] != '|'))
			return (my_print(str[1]));
	}
	if (strlen(str) == 3)
		return (my_print(str[2]));
	if (strlen(str) > 3)
	{
		if (str[0] == '|')
			my_print(str[2]);
		else
		{
			fd_putstr("minishell: syntax error near unexpected token `", 2);
			fd_putchar(str[2], 2);
			fd_putchar(str[2], 2);
			fd_putstr("'\n", 2);
		}
		return (-1);
	}
	return (0);
}

int	check_p2(char *str, char *tm)
{
	if (tm != NULL)
	{
		if (!(((str[0] == '<' && str[1] == '<') || (str[0] == '>'
						&& str[1] == '>') || str[0] == '>'
					|| str[0] == '<') && tm[0] == '|'))
			return (my_print(str[0]));
	}
	if (check_p1(str) == -1)
		return (-1);
	return (0);
}

int	check_sp(t_token *token)
{
	t_token	*tmp;
	char	*part;
	char	*tm;
	int		i;

	tmp = token;
	tm = NULL;
	if (token->token[0] == '|')
		return (my_print(token->token[0]));
	while (1)
	{
		part = strchr("<>|", token->token[0]);
		if (part != NULL)
		{
			if (check_p2(token->token, tm) == -1)
				return (-1);
			if (token->next == NULL)
				return (my_print('\0'));
			tm = part;
		}
		else
			tm = NULL;
		token = token->next;
		i = 0;
		if (token != NULL && token->next == NULL)
		{
			while (token->token && token->token[i] == ' ')
				i++;
			if (token->token[i] == '\0')
				return (my_print('\0'));
		}
		if (token == NULL)
			break ;
	}
	token = tmp;
	return (0);
}
