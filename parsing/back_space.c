/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:58:13 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/19 16:50:28 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	r_cleang(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] && !(str[i] == '`'))
			i++;
		if (str[i])
			str[i] = '\2';
		while (str[i] && str[i] != '`')
			i++;
		if (str[i])
			str[i] = '\2';
	}
}

char	*cleang(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = ft_calloc((ft_strlen(str) + 1), sizeof(char));
	r_cleang(str);
	while (str[i])
	{
		if (str[i] && !(str[i] == '\2' || str[i] == '\4'))
			new[j++] = str[i++];
		else if (str[i] && str[i] == '\4')
		{
			new[j++] = '\6';
			i++;
		}
		else
			i++;
	}
	free(str);
	return (new);
}

void	save_qutes_1(char *str, int end, char ___char)
{
	while (str[end] && str[end] == ___char)
	{
		if (str[end + 1] && str[end + 1] == ___char)
		{
			str[end + 1] = '\1';
			str[end] = '\1';
			end++;
		}
		if (str[end])
			end++;
	}
}

char	*mother_str(char *str, int i, int end, int start)
{
	if (str == NULL)
		return (NULL);
	back_origin(str);
	while (str[i])
	{
		while (str[i] && (str[i] == '\6' || str[i] == '\4' || str[i] == '\7'))
		{
			end++;
			i++;
		}
		start = i - end - 1;
		if (end != 0)
		{
			if (start > 0 && str[start]
				&& (str[start] == '\"' || str[start] == '\''))
				save_qutes(str, start, str[start]);
			end = i;
			if (str[end] && (str[end] == '\"' || str[end] == '\''))
				save_qutes_1(str, end, str[end]);
		}
		end = 0;
		i++;
	}
	flaying_qutes(str);
	return (cleang(str));
}

t_table	*back_space(t_table *table, int i)
{
	table->commend = remouve_char(table->commend, '\7');
	table->commend = mother_str(table->commend, 0, 0, 0);
	while (table->arg[++i])
	{
		table->arg[i] = remouve_char(table->arg[i], '\7');
		table->arg[i] = mother_str(table->arg[i], 0, 0, 0);
	}
	i = -1;
	while (table->files[++i])
	{
		if (ft_strchr(table->files[i], '\5') || table->next[i] == 1)
		{
			if (ft_strchr(table->files[i], '\'') || ft_strchr(table->files[i], '\"'))
				table->next[i] = 4;
		}
		table->files[i] = mother_str(table->files[i], 0, 0, 0);
	}
	i = -1;
	while (table->option[++i])
	{
		table->option[i] = remouve_char(table->option[i], '\7');
		table->option[i] = mother_str(table->option[i], 0, 0, 0);
	}
	return (table);
}
