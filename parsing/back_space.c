/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:58:13 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/09 17:02:50 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *hanty_7ada_wlat_wa7da_khera(char *str)
{
	int		i;
	// int		j;
	// int		count;
	// char	*new;
	i = 0;
	// j = 0;
	if (str == NULL)
		return(NULL);
	// count = strlen(str);
	// new = calloc((count * 2), sizeof(char));
	// i = 0;
	// if (strchr(str, '\2') && (str[i] == '\'' || str[i] == '\"'))
	// {
	// 	str[count - 1] = '\2';
	// 	str[i] = '\2';
	// }
	// while(str[i])
	// {
	// 	if (str[i] == '\2' && (i == 0 || i == count - 1))
	// 		i++;
	// 	else if (str[i] == '\2')
	// 		new[j++] = ' ';
	// 	if (i != 0 && i != count - 1 && (str[i] == '\"' || str[i] == '\'') && (str[i + 1] == '\'' || str[i + 1] == '\"'))
	// 	{
	// 		i++;
	// 		i++;
	// 		new[j++] = ' ';
	// 		// i++;
	// 	}
	// 	new[j++] = str[i++];
	// }
	// free(str);
	while(str[i])
	{
		if(str[i] == '\5')
		{
			str[i] = '$';
		}
		i++;
	}
	i = 0;
	int j;
	j = 0;
	char *new;
	if (str == NULL)
		return(NULL);
	new = calloc((ft_strlen(str) + 1), sizeof(char));
	if (strchr(str, '\2'))
	{
		while(str[i])
		{
			if (str[i] == '\2')
				str[i] = ' ';
			i++;
		}
	}
	i = 0;
	char c;
	while(str[i])
	{
		while(str[i] && !(str[i] == '\"' || str[i] == '\'' || str[i] == '`'))
			i++;
		if (i == 0 && str[i] && str[i+1] && str[i] == str[i + 1] && ( str[i + 2] == '\0' || str[i + 2] == ' '))
			i++; 
		else if (str[i] && str[i+1] &&  str[i] == str[i + 1] && ( str[i + 2] == '\0' || str[i + 2] == ' ') && i > 0 && str[i - 1] == ' ')
			i++; 
		else
		{	
			c = str[i];
			if (str[i])
				str[i] = '\2';
			while(str[i] && str[i] != c)
				i++;
			if (str[i])
				str[i] = '\2';
		}
		if (str[i])
			i++;
	}
	i = 0;
	while(str[i])
	{
		while(str[i] && !(str[i] == '`'))
			i++;
		if (str[i])
			str[i] = '\2';
		while(str[i] && str[i] != '`')
			i++;
		if (str[i])
			str[i] = '\2';
		// if (str[i])
		// 	i++;
	}
	i = 0;
	while (str[i])
	{
		if (str[i]  && str[i] != '\2')
			new[j++] = str[i++];
		else
			i++;
	}
	free(str);
	return(new);
}
t_table *back_space(t_table *table)
{
	int i;

	i = -1;
	table->commend = hanty_7ada_wlat_wa7da_khera(table->commend);
	while(table->arg[++i])
		table->arg[i] = hanty_7ada_wlat_wa7da_khera(table->arg[i]);
	i = -1;
	while(table->files[++i])
	{
		if (strchr(table->files[i], '\5'))
		{
			if (strchr(table->files[i], '\'') || strchr(table->files[i], '\"'))
				table->next[i] = 4;
		}
		else if(strchr(table->files[i], '\'') || strchr(table->files[i], '\"'))
			table->next[i] = 4;
		table->files[i] = hanty_7ada_wlat_wa7da_khera(table->files[i]);
	}
	i = -1;
	while(table->option[++i])
		table->option[i] = hanty_7ada_wlat_wa7da_khera(table->option[i]);
	return(table);
}