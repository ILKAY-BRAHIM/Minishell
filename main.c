/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 03:05:06 by bchifour          #+#    #+#             */
/*   Updated: 2023/03/25 03:17:47 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_table *table;
	(void)argc;
	(void)argv;
	int i;
	i = 0;
	
	while(env[i])
	{
		table->env[i] = env[i];
		printf ("%s\n", table->env[i]);
		i++;
	}
}