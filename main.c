/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 00:27:11 by bchifour          #+#    #+#             */
/*   Updated: 2023/03/30 06:47:48 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_table *table;
	char *line;

	(void)argc; 
	(void)argv;
	// init_env();
	while (1)
	{
		line = get_prompt();
		lexer(line);
		// parsing()
		// excution();
	}
}