/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 03:05:06 by bchifour          #+#    #+#             */
/*   Updated: 2023/04/05 23:15:07 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **origin_env)
{
	t_table *table;
	t_env	*env;
	char *line;
	char *array;
	int i;

	(void)argc; 
	(void)argv;
	env = init_env(origin_env);
	while (1)
	{
		i = 0;
		line = get_prompt();
		array = parsing(line);
		table = lexer(array);
		// execution(table);
		while(1)
		{
			printf ("comend :     %s\n", table[i].commend); // test
			printf ("option :     %s\n", table[i].option); // test
			printf ("arg    :     %s\n", table[i].arg); // test
			printf ("i_file :     %s\n", table[i].i_file); // test
			printf ("o_file :     %s\n", table[i].o_file); // test
			printf ("end    :     %s\n", table[i].stop); // test
			printf ("next   :     %d\n", table[i].next); // test
			if(!table[i].next)
				break;
			i++;
		}
	}
}