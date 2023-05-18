/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_back_space.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:25:12 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/18 20:34:15 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	back_origin(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\5')
		{
			str[i] = '$';
		}
		i++;
	}
	i = 0;
	if (strchr(str, '\2'))
	{
		while (str[i])
		{
			if (str[i] == '\2')
				str[i] = ' ';
			i++;
		}
	}
}

int	flaying_qutes_n(char *str, int i, char c)
{
	if (i == 0 && str[i] && str[i + 1] && str[i] == str[i + 1]
		&& (str[i + 2] == '\0' || str[i + 2] == ' '))
	{
		str[i++] = '\1';
		str[i] = '\1';
	}
	else if (str[i] && str[i + 1]
		&& str[i] == str[i + 1] && (str[i + 2] == '\0'
			|| str[i + 2] == ' ' ) && i > 0 && str[i - 1] == ' ')
	{
		str[i++] = '\1';
		str[i] = '\1';
	}
	else
	{	
		c = str[i];
		if (str[i])
			str[i] = '\2';
		while (str[i] && str[i] != c)
			i++;
		if (str[i])
			str[i] = '\2';
	}
	return (i);
}

void	flaying_qutes(char *str)
{
	int		i;
	char	c;

	i = 0;
	c = '\0';
	if (ft_strlen(str) == 3 && (str[0] == '\"' || str[0] == '\'')
		&& str[1] == '\7' && (str[2] == '\"' || str[i] == '\''))
		str[1] = '\1';
	while (str[i])
	{
		while (str[i] && !(str[i] == '\"' || str[i] == '\'' || str[i] == '`'))
			i++;
		i = flaying_qutes_n(str, i, c);
		if (str[i])
			i++;
	}
}

void	save_qutes(char *str, int start, char __char)
{
	while (start >= 0 && str[start] && str[start] == __char)
	{
		if (start > 0 && str[start - 1] == __char)
		{
			str[start] = '\1';
			str[start - 1] = '\1';
			start--;
		}
		if (start >= 0)
			start--;
	}
}
