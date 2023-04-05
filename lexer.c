/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 05:37:29 by bchifour          #+#    #+#             */
/*   Updated: 2023/04/05 12:48:48 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cont_sp(char *line)
{
	int i;
	int cont;

	i = 0;
	cont = 1;
	while (line[i])
	{
		if (line[i] == '|')
			cont++;
		else if (line[i] == '>' && line[i+1] == '>')
		{
			cont++;
			i++;
		}
		else if (line[i] == '<' && line[i+1] == '<')
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
int *collect_sp(char *line)
{
	int cont;
	int *array;
	int i;

	i = 0;
	cont = cont_sp(line);
	array = calloc(cont, sizeof(int));
	cont = 0;
	while (line[i])
	{
		if (line[i] == '|')
			array[cont++] = PIPE;
		else if (line[i] == '>' && line[i+1] == '>')
		{
			array[cont++] = O_APPEND;
			i++;
		}
		else if (line[i] == '<' && line[i+1] == '<')
		{
			array[cont++] = HERE_DOC;
			i++;
		}
		else if (line[i] == '>')
			array[cont++] = R_OUTPUT;
		else if (line[i] == '<')
			array[cont++] = R_INPUT;
		i++;
	}
	return (array);
}
int tokens(char *line, t_table *table, t_var *var)
{
	char *token;
	int i;
	int j;

	i = 0;
	j = 0;
	var->split = calloc(cont_sp(line)+1, sizeof(char *));
	token = strtok(line, "<>|");
	while(token != NULL)
	{
		var->split[i] = strdup(token);
		table[i].next = var->array[j];
		token = strtok(NULL, "<>|");
		i++;
		j++;
	}
	return (i);
}

void	saver(t_table *table, t_var *var, int i)
{
	int j;
	int n;
	int b;
	int tfo;
	int count;

	j = 0;
	while (j < i)
	{
		n = 0;
		count = 0;
		var->tokens = ft_split(var->split[j], ' ', &tfo);
		while(var->tokens[n])
		{
			if (strchr(var->tokens[n], '\"'))
			{
				n++;
				while(!strchr(var->tokens[n], '\"'))
					n++;
				b = 1;
				while (b <= n)
				{
					var->tokens[0] = ft_strjoin(var->tokens[0], strdup(" "));
					var->tokens[0] = ft_strjoin(var->tokens[0], var->tokens[b++]);
				}
				table[j].commend = strdup(var->tokens[0]);
				break;
			}	
			else 
			{
				table[j].commend = strdup(var->tokens[n]);
				break;
			}
				
		}
		n++;
		printf ("comend %s\n", table[j].commend); // test
		if (var->tokens[n] && var->tokens[n][0] == '-')
		{
			table[j].option = strdup(var->tokens[n]);
			printf ("option %s\n", table[j].option); // test
			n++;
			tfo--;
		}
		// table[j].arg = calloc(tfo, sizeof(char **));
		if (var->tokens[n])
		{
			// strnstr(var->split[j],var->tokens[n], -1);
			table[j].arg = strdup(strnstr(var->split[j],var->tokens[n], -1));
			printf ("arg %s\n", table[j].arg); // test
			n++;
			count++;
		}
		if (table[j].next == R_INPUT)
		{
			table[j].i_file = strdup(var->split[j + 1]);
			printf ("i_file %s\n", table[j].i_file); // test
			j++;
		}
		else if (table[j].next == R_OUTPUT || table[j].next == O_APPEND)
		{
			table[j].o_file = strdup (var->split[j + 1]);
			printf ("o_file %s\n", table[j].o_file); // test
			j++;
		}
		else if (table[j].next == HERE_DOC)
		{
			table[j].i_file = strdup("STDIN");
			table[j].stop = strdup(var->split[j + 1]);
			printf ("i_file %s\n", table[j].i_file); // test
			printf ("end %s\n", table[j].stop); // test
			j++;
		}
		j++;
	}
}

void	lexer(char *line)
{
	t_table *table;
	t_var *var;
	int i;

	var = calloc(sizeof(t_var), 1);
	var->array = collect_sp(line); // need to free array
	table = calloc(cont_sp(line), sizeof(t_table));
	i = tokens(line, table, var);
	// check()
	saver(table, var, i);
	
	
}