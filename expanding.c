/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:14:35 by bchifour          #+#    #+#             */
/*   Updated: 2023/04/07 17:21:59 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*expanding(char *line)
{
	int i;
	char *parts;
	char *var;

	i = 0;
	while[line[i]]
	{
		if (line[i] != '$')
			parts = ft_strnchr(line, line[0], ' ', 1);
		var = ft_strnchr(line, '$', ' ', i);
		i++;
	}
}