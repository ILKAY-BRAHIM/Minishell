/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:58:13 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/02 18:06:49 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *hanty_7ada_wlat_wa7da_khera(char *str)
{
	int		i;
	int		j;
	int		count;
	char	*new;

	i = 0;
	j = 0;
	if (str == NULL)
		return(NULL);
	count = ft_strlen(str);
	new = calloc(count + 1, sizeof(char));
	i = 0;
	if (strchr(str, '\2') && (str[i] == '\'' || str[i] == '\"'))
	{
		str[count - 1] = '\2';
		str[i] = '\2';
	}
	while(str[i])
	{
		if (str[i] == '\2' && (i == 0 || i == count - 1))
			i++;
		else if (str[i] == '\2')
			new[j++] = ' ';
		new[j++] = str[i++];
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
		table->files[i] = hanty_7ada_wlat_wa7da_khera(table->files[i]);
	i = -1;
	while(table->option[++i])
		table->option[i] = hanty_7ada_wlat_wa7da_khera(table->option[i]);
	return(table);
}