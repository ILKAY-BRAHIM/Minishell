/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:18:46 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/19 16:51:13 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	flay_gard(char *data, int i, int index, char _char)
{
	while (data[i])
	{
		while (data[i] && !(data[i] == '\"'
				|| data[i] == '\'' || data[i] == '`'))
			i++;
		_char = data[i];
		if (data[i] == _char && index == 1)
			index = -1;
		if (data[i])
			i++;
		while (data[i] && data[i] != _char && index == -1)
		{
			if (data[i] && data[i] == ' ' && index == -1)
			{
				(_char == '`') && (data[i] = '\4');
				(_char != '`') && (data[i] = '\2');
			}
			i++;
		}
		if (data[i] == _char && index == -1)
			index = 1;
		if (data[i])
			i++;
	}
}

void	gards(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(str[i], '`'))
		{
			str[i] = sp_strjoin(str[i], "`", 0);
			i++;
			while (str[i] && !(ft_strchr(str[i], '`')))
			{
				str[i] = sp_strjoin("`", str[i], 1);
				str[i] = sp_strjoin(str[i], "`", 0);
				i++;
			}
			str[i] = sp_strjoin("`", str[i], 1);
			i++;
		}
		else if (str[i])
			i++;
	}
}

void	save_tkones(char **str, char **tokons, int y, int *_char)
{
	while (str[y] && str[y][1] == '-' && *_char == 0)
	{
		if (ft_strlen(str[y]) == 2
			&& str[y][0] == '`' && str[y][1] == '`')
			y++;
		else
		{
			tokons[2] = sp_strjoin(tokons[2], str[y], 0);
			tokons[2] = sp_strjoin(tokons[2], ft_strdup(" "), 2);
			y++;
		}
	}
	while (str[y])
	{
		if (ft_strlen(str[y]) == 2
			&& str[y][0] == '`' && str[y][1] == '`')
			y++;
		else
		{
			tokons[3] = sp_strjoin(tokons[3], str[y], 0);
			tokons[3] = sp_strjoin(tokons[3], ft_strdup(" "), 2);
			*_char = 1;
			y++;
		}
	}
}

void	save_tkones_1(char **str, char **tokons, int u, int *_char)
{
	while (str[u] && (str[u][1] == '-'))
	{
		if (ft_strlen(str[u]) == 2
			&& str[u][0] == '`' && str[u][1] == '`')
			u++;
		else
		{
			tokons[2] = sp_strjoin(tokons[2], str[u], 0);
			tokons[2] = sp_strjoin(tokons[2], ft_strdup(" "), 2);
			u++;
		}
	}
	while (str[u])
	{
		if (ft_strlen(str[u]) == 2
			&& str[u][0] == '`' && str[u][1] == '`')
			u++;
		else
		{
			*_char = 1;
			tokons[3] = sp_strjoin(tokons[3], str[u], 0);
			tokons[3] = sp_strjoin(tokons[3], ft_strdup(" "), 2);
			u++;
		}
	}
}

void	norm_(char *str, char **tokons, int *_char)
{
	int		y;
	char	**array;

	y = 0;
	if (ft_strchr(str, '\4'))
	{
		array = ft_split(str, '\4');
		gards(array);
		save_tkones(array, tokons, 0, _char);
		free_array(array);
	}
	else
	{
		*_char = 1;
		tokons[3] = sp_strjoin(tokons[3], str, 0);
		tokons[3] = sp_strjoin(tokons[3], ft_strdup(" "), 2);
	}
}
