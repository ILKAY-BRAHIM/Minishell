/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 09:26:35 by rrasezin          #+#    #+#             */
/*   Updated: 2023/04/07 18:25:45 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_table *table, int i)
{
	int	j;

	j = 0;
	if (table[i].o_file == NULL)
	{
		if (table[i].arg != NULL)
			printf("%s", table[i].arg);
		if (table[i].option == NULL || ft_strncmp(table[i].option, "-n", -1) != 0)
			printf("\n");
	}
	//need to add the part when i have deffrent o_file in the pipe and rederection case 
	return ;
}