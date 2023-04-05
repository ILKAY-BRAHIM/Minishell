/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 03:05:06 by bchifour          #+#    #+#             */
/*   Updated: 2023/04/05 14:53:41 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **origin_env)
{
	t_table *table;
	t_env	*env;
	char *line;
	char *array;

	(void)argc; 
	(void)argv;
	// env = init_env(origin_env);
	while (1)
	{
		line = get_prompt();
		array = parsing(line);
		lexer(array);
		// excution();
	}
}