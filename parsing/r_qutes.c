/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_qutes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 01:05:41 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/04 23:08:32 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	new_str(char *str)
{
	int		i;
	int		index;
	char	c;
	int		x;
	int		remove;

	i = 0;
	while(str[i])
	{
		remove = 0;
		while(str[i] && (str[i] != '\"' && str[i] != '\''))
			i++;
		c = str[i];
		index = i;
		i++;
		while(str[i] && str[i] != c)
		{
			if (str[i] == ' ')
				remove = 1;
			i++;
		}
		if (index + 1 == i && index - 1 > 0 && str[index - 1] == ' ' &&  (str[i + 1] == ' ' || str[i + 1] == '\0'))
			x = 0;
		else if ((str[0] == '\"' || str[0] == '\'') && ( str[1] == '\"' || str[1] == '\'') && str[2] == ' ')
			x = 0;
		else if (str[i] && remove == 0 )
		{
			str[index] = '\2';
			str[i] = '\2';
		}
		i++;
	}
}
void	r_str(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '(' || str[i] == ')')
			str[i] = '\2';
		i++;
	}
}
int		collect(char *str)
{
	int i;
	int count;

	i = 0;
	count = 1;
	while(str[i])
	{
		if (str[i] && str[i] == '\2')
			count++;
		i++;
	}
	return (count);
}
char	*c_str(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = calloc((strlen(str) - collect(str)) + 2 , 1);
	while(str[i])
	{
		if (str[i] == '\2')
			i++;
		else if (str[i])
			new[j++] = str[i++];
	}
	return (new);
}
t_token *r_qutes(t_token *tokens)
{
	t_token *new;
	t_token *tmp;
	int count;
	char *str;

	tmp = tokens;
	count = 1;
	while(1)
	{
		if (strchr(tokens->token, '\"') || strchr(tokens->token, '\''))
			new_str(tokens->token);
		if (strchr(tokens->token, '(') || strchr(tokens->token, ')'))
			r_str(tokens->token);
		str = c_str(tokens->token);
		if (count == 1)
			new = new_token(str);
		else
			lst_add_back(new, new_token(str));
		count++;
		free(str);
		tokens = tokens->next;
		if (tokens == NULL)
			break ;
	}
	// free_lst(tmp);
	return(new);
}