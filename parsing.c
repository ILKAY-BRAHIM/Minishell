/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 01:33:32 by bchifour          #+#    #+#             */
/*   Updated: 2023/04/06 17:16:53 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "minishell.h"

char *alloc_line(char *line)
{
	char *linee;

	linee = calloc(strlen(line) + (cont_sp(line) * 2) + 1, sizeof (char));
	return (linee);
}
void	replace(char *str, int end, char cu, char re)
{
	int i;
	i = 0;
	while(str && i < end)
	{
		if (str[i] == cu)
			str[i] = re;
		i++;
	}
}
void	is_valid_quate(char *array)
{
	int i;
	char *first;
	char *end;
	int x;
	char *tmp;
	char **split;
	
	tmp = array;
	while(tmp)
	{
		// printf("replace %s\n",tmp);
		first = strchr(tmp, '\"');
		if (first == NULL)
			break;
		end = strchr(first+1, '\"');
		if (end == NULL)
			break;
		i = strlen(tmp) - strlen(first);
		x = strlen(end);
		replace(tmp+i, strlen(first) - x, ' ', '*');
		tmp = end+1;
	}
	split = ft_split(array, ' ', &i);
	if (strchr(split[0], '*'))
		printf("\033[0;31msyntax error (is valid qute)\033[0;37m\n");
	// printf("replace %s\n",array);
}

void	check_quate(char *line)
{
	char *token;
	char **array;
	char *tmp;
	int i;
	int error;
	int j;
	int x;

	i = 0;
	tmp = strdup(line);
	array = calloc(cont_sp(line) + 1, sizeof(char *));
	token = strtok(tmp, "<>|");
	while(token != NULL)
	{
		array[i] = strdup(token);
		token = strtok(NULL, "<>|");
		i++;
	}
	i = 0;
	while (array[i])
	{
		error = 0;
		j = 0;
		x = 1;
		while (array[i][j])
		{
			if (array[i][j] == '\"')
			{
				error++;
				x = 1;
			}
			j++;
		}
		if (error % 2 != 0)
		{
			printf("\033[0;31msayntax error (check_quate)\033[0;37m\n");
			exit (1);
			i = 0;
		}
		// else if (x == 1)
		// 	is_valid_quate(array[i]);
		i++;
	}
	
}

char	*space_line(char *line)
{
	char *array;
	int i;
	int j;

	i = 0;
	j = 0;
	array = alloc_line(line);
	check_quate(line);
	while(line[i])
	{
		if (line[i] == '|')
		{
			array[j++] = ' ';
			array[j++] = line[i++];
			array[j++] = ' ';
		}
		else if (line[i] == '>' && line[i+1] == '>')
		{
			array[j++] = ' ';
			array[j++] = line[i++];
			array[j++] = line[i++];
			array[j++] = ' ';
		}
		else if (line[i] == '<' && line[i+1] == '<')
		{
			array[j++] = ' ';
			array[j++] = line[i++];
			array[j++] = line[i++];
			array[j++] = ' ';
		}
		else if (line[i] == '>')
		{
			array[j++] = ' ';
			array[j++] = line[i++];
			array[j++] = ' ';
		}
		else if (line[i] == '<')
		{
			array[j++] = ' ';
			array[j++] = line[i++];
			array[j++] = ' ';
		}
		else if (line[i])
			array[j++] = line[i++];
	}
	return (array);
	
}
int		check_op(char *array, char *sp)
{
	char **sp_p;
	int i;
	int tfo;

	sp_p = ft_split(sp, ' ', &tfo); // need to free her and remouve tfo
	i = 0;
	while(sp_p[i])
	{
		if (strcmp(array, sp_p[i]) == 0)
			return(1);
		i++;
	}
	return (0);
}
void	check_clean(char **array)
{
	int i;

	i = 0;
	while(array[i])
	{
		if (check_op(array[i], "| >> << > <") && i == 0)
			printf("\033[0;31msayntax error1\033[0;37m\n");
		if (check_op(array[i], "| >> << > <"))
		{
			if (array[i + 1] && check_op(array[i + 1], "| >> << > <"))
				printf("\033[0;31msayntax error2\033[0;37m\n");
		}
		i++;
	}
	if (check_op(array[i - 1], "| >> << > <"))
		printf("\033[0;31msayntax error3\033[0;37m\n");
}
int	skip(char *line)
{
	char *first = strchr(line, '\"');
	if (first == NULL )
		return (1);
	char *end = strchr(first+1, '\"');
	if (end == NULL)
		return (0);
	int i = strlen(first);
	int x = strlen(end);
	i = i - x;
	x = 0;
	while(x < i)
	{
		// printf("%c\n", first[x]);
		if (first[x] == ' ')
		{
			return (0);
		}
		x++;
	}
	return (1);
}
char *remouve_quote(char *line)
{
	char *array;
	int i;
	int j;

	array = calloc(strlen(line), sizeof(char));
	i = 0;
	j = 0;
	while(line[i])
	{
		if (line[i] == '\"')
		{
			if (skip(line+i))
			{
				i++;
				while(line[i] != '\"')
				{
					array[j] = line[i];
					j++;
					i++;
				}
				i++;
			}
			else 
				array[j++] = line[i++];
		}
			else if (line[i])
				array[j++] = line[i++];
	}
	return (array);
}
t_table	*parsing(char *line)
{
	t_table *table;
	char *linee;
	char **array;
	int	tfo;
	linee = space_line(line);
	// printf("-----   %s\n", line);
	array = ft_split(linee, ' ', &tfo);
	check_clean(array);
	line = remouve_quote(linee);
	table = lexer(line);
	return (table);
	
	
}

// int main()
// {
// 	char line[50] = "\"ls -la\" |gr\"ep\" \" .c \"   \" .     \">>txt.txt ";
// 	printf("%s\n", parsing(line));
// }