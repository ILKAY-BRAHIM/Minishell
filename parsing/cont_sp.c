/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cont_sp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 01:34:18 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/17 17:34:00 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_sp(char *line, int i, int cont)
{
	while (line[i])
	{
		if (line[i] == '|')
			cont++;
		else if (line[i] == '>' && line[i + 1] == '>')
		{
			cont++;
			i++;
		}
		else if (line[i] == '<' && line[i + 1] == '<')
		{
			cont++;
			i++;
		}
		else if (line[i] == '>')
			cont++;
		else if (line[i] == '<')
			cont++;
		i++;
	}
	return (cont);
}
