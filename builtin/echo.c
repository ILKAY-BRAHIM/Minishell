/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 09:26:35 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/10 15:54:03 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// changed

int	ft_echo(t_table *table, t_env *env)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (table->option[i] != NULL)
	{
		if (ft_strncmp(table->option[0], "-n", 2) == 0)
		{
			while (table->option[0][j] == 'n')
				j++;
			if (table->option[0][j] == '\0')
				i++;
		}
		while (table->option[i])
		{
			printf("%s", table->option[i]);
			i++;
			if (table->arg[0] != NULL)
				printf(" ");
		}			
	}
	i = 0;
	while (table->arg && table->arg[i])
	{
		printf("%s", table->arg[i]);
		i++;
		if (table->arg[i] != NULL)
			printf(" ");
	}
	if (table->option[0] == NULL || ft_strncmp(table->option[0], "-n", 2) != 0)
		printf("\n");
	rm_env_var(&env, "_");
	new_env_var(env, ft_strjoin("_=", ft_strdup("echo")), 0);
	return (0);
}

