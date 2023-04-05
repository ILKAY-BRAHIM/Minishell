/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 09:26:35 by rrasezin          #+#    #+#             */
/*   Updated: 2023/04/05 14:19:11 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_table *cmd)
{
	int	i;

	i = 0;
	while (cmd->arg[i])
	{
		printf("%s", cmd->arg[i]);
		if (cmd->arg[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (cmd->option == NULL || ft_strncmp(cmd->option, "-n", 2) != 0)
		printf("\n");
	return ;
}