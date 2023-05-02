/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_v3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:02:43 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/02 18:06:49 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/utils.h"
#include <string.h>
#include <stdio.h>

t_token *parsing_v3(char *line, t_env *env)
{
	int i;
	t_token *token;
	t_token *new;
	t_token *tmp;
	char *part;
	int count;

	count = 0;
	i = 0;
	while(line[i])
	{
		if (line[i] == '$' && (line[i + 1] == '\"' || line[i + 1] == '\'') && count == 0)
		{
			line[i] = '\2';
			count = 1;
		}
		if (line[i] == '$' && (line[i + 1] == '\"' || line[i + 1] == '\'') && count != 0)
			count = 0;
		if (line[i] == '\"' || line[i] == '\'')
			count = 1;
		i++;
	}
	count = 1;
	i = 0;
	while(line[i])
	{
		// i = 0;
		// while((line[i] && line[i] != '\"' && line[i] != '\'')) // serch for (") and (')
		// {
		// 	if (line[i] == '$' && (line[i + 1] == '\"' || line[i + 1] == '\'')) // remove $ if ($"")
		// 		line[i] = ' ';
		// 	i++;
		// }
		// if (line[i] && (line[i] != '\"' && line[i] != '\'') && i != 0 && line[i - 1] == '$') // get first part that doesn't have quotes
		// {
		// 	part = get_part(line, line[0], line[i - 1], 0); // flag 0 in ft_strnchr control the return of function non include end of part
		// 	printf("PART 0  %s\n", part);
		// 	if (part == NULL)
		// 		break ;
		// 	line = line + (strlen(part) + 1);
		// }
		// else // get part that have quotes
		// {
		// 	part = get_part(line, line[0], line[i], 0);
		// 	printf("%c   %c\n", line[0], line[i]);
		// 	printf("PART 1  |%s|\n", part);
		// 	sleep(1);
		// 	if (part == NULL)
		// 		break ;
		// 	line = line + strlen(part);
		// }
		// if (count == 1)
		// {
			
		// 	token = new_token(part);
		// 	// printf("PART 2  %s\n", part);
		// }
		// else if (count > 1)
		// 	lst_add_back(token, new_token(part));
		// count++;
		// free(part);


		if (line[0] == '\"' || line[0] == '\'')
		{
			part = get_part(line, line[0], line[0], 0);
			if (count == 1)
				token = new_token(part);
			else 
				lst_add_back(token, new_token(part));
		}
		else 
		{
			while(line[i] && (line[i] != '\"' && line[i] != '\''))
				i++;
			part = get_part(line, line[0], line[i], 2);
			if (count == 1)
				token = new_token(part);
			else 
				lst_add_back(token, new_token(part));
		}
		line = line + strlen(part);
		free(part);
		count++;
		i = 0;
	} 
	// free(part);
	count = 1;
	tmp = token;

	t_token *tmp_frr;
	while(1)
	{
		if(count == 1)
		{
			new = check_token(tmp->token, env);
			if (new == NULL)
			{
				free_lst(token);
				return(NULL);	
			}
		}
		else 
		{
			tmp_frr = check_token(tmp->token, env);
			// pause();
			if (tmp_frr == NULL)
			{
				free_lst(token);
				// free(tmp_frr);
				return (NULL);
			}
			lst_add_back(new, tmp_frr);
			// free_lst(tmp_frr);
			// free linked list;
		}
	 	tmp = tmp->next;
		if (tmp == NULL)
			break;

		count++;
	}
		// printf("OK\n");
	// free_lst(token);
	new = join_tokens(new);
	if (check_sp(new) == -1)
		return (NULL);
	new = r_qutes(new);
	new = join_tokens2(new);
	return (new);
}