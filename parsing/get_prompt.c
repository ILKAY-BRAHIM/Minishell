/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:47:36 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/02 18:06:49 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_prompt(void)
{
	char *line;
	int		i;

	i = 0;
	line = readline("\033[1;35mminishell ~ \033[0;37m");
	while(line[i] == ' ')
		i++;
	if (line[i] == '\0')
	{
		free(line);
		return(NULL);
	}
	else
		add_history(line);
	return (line);
}