/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:58:13 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/16 00:40:48 by bchifour         ###   ########.fr       */
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
	new = calloc((ft_strlen(str) + 1), sizeof(char));
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

char	*hanty_7ada_wlat_wa7da_khera(char *str)
{
	int		i;
	int		start;
	int		end;

	i = 0;
	end = 0;
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

t_table *back_space(t_table *table)
{
	int	i;

	i = -1;
	table->commend = remouve_char(table->commend, '\7');
	table->commend = hanty_7ada_wlat_wa7da_khera(table->commend);
	while (table->arg[++i])
	{
		table->arg[i] = remouve_char(table->arg[i], '\7');
		table->arg[i] = hanty_7ada_wlat_wa7da_khera(table->arg[i]);
	}
	i = -1;
	while (table->files[++i])
	{
		if (strchr(table->files[i], '\5') || table->next[i] == 1)
		{
			if (strchr(table->files[i], '\'') || strchr(table->files[i], '\"'))
				table->next[i] = 4;
		}
		table->files[i] = hanty_7ada_wlat_wa7da_khera(table->files[i]);
	}
	i = -1;
	while (table->option[++i])
	{
		table->option[i] = remouve_char(table->option[i], '\7');
		table->option[i] = hanty_7ada_wlat_wa7da_khera(table->option[i]);
	}
	return (table);
}
