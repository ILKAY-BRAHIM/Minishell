/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:22:58 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/17 17:34:24 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

void	_tok(char *str, char **tok, int att, char *sp)
{
	int		i;
	int		j;
	char	*token;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i])
			token = strchr(sp, str[i]);
		if (token && str[i])
		{
			token = get_part(str, str[0], token[0], att);
			tok[j++] = ft_strdup(token);
			ft_memmove(str, str + strlen(token),
				strlen(str + strlen(token)) + 1);
			free(token);
			i = 0;
		}
		else if (str[i])
			i++;
	}
	if (*str != '\0')
		tok[j++] = strdup(str);
	tok[j] = NULL;
}

char	**ft_strtok(char *strw, char *sp, int att)
{
	int		i;
	int		j;
	char	**tok;
	char	*str;

	i = 0;
	j = 0;
	tok = NULL;
	str = strdup (strw);
	if (att == 1)
		tok = ft_calloc(count_sp(str, 0, 1) + 1, sizeof(char *));
	else if (att == 2)
		tok = ft_calloc(count(str) + 1, sizeof(char *));
	_tok(str, tok, att, sp);
	free(str);
	return (tok);
}
